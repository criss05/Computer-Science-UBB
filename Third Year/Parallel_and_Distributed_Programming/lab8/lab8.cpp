#include <mpi.h>
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>
#include <windows.h>

// --- CONFIGURATION ---
// Total integer variables in the system
const int NUM_VARS = 5;

// Message Tags
#define TAG_WRITE_REQ 1
#define TAG_WRITE_RES    2
#define TAG_CAS_REQ   3
#define TAG_CAS_RESP  4
#define TAG_STOP      99

struct UpdateMessage {
    int var_id;
    int value;
};

struct CASRequest {
    int var_id;
    int expected;
    int new_value;
};

struct CASResponse {
    bool success;
    int current_value;
};

class DSM {
private:
    int rank;
    int size;
    std::map<int, int> variables;
    std::map<int, std::vector<int>> subscribers;
    std::function<void(int, int)> onChangeCallback;
    std::thread listenerThread;
    bool running;

    // Mutex for variable access
    std::mutex var_mtx;

    // Mutex for MPI calls (Crucial for thread safety in MPI)
    std::mutex mpi_mtx;

public:
    DSM() : running(true) {}

    void init(int argc, char** argv) {
        // Initialize MPI with Thread Support
        int provided;
        MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
        if (provided < MPI_THREAD_MULTIPLE) {
            std::cerr << "Warning: MPI implementation does not support full multithreading.\n";
        }

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        for (int i = 0; i < NUM_VARS; i++) variables[i] = 0;

        // Subscribe everyone to everything for this lab
        for (int v = 0; v < NUM_VARS; v++) {
            for (int r = v%2; r < size; r+=2) subscribers[v].push_back(r);
        }

        listenerThread = std::thread(&DSM::listen, this);
    }

    ~DSM() {
        stop();
        if (listenerThread.joinable()) listenerThread.join();
        MPI_Finalize();
    }

    void setCallback(std::function<void(int, int)> cb) { onChangeCallback = cb; }
    int getRank() { return rank; }
    int getSize() { return size; }
    int getOwner(int var_id) { return var_id % size; }

    bool isSubscriber(int var_id) {
        const auto& subs = subscribers[var_id];
        return std::find(subs.begin(), subs.end(), rank) != subs.end();
    }

    // --- FIX 1: WRITE ---
    void write(int var_id, int value) {
        if (!isSubscriber(var_id)) return;

        int owner = getOwner(var_id);

        if (owner == rank) {
            // I am the owner. Don't send MPI. Execute logic directly.
            sendBroadcast(var_id, value);
        }
        else {
            UpdateMessage msg = { var_id, value };
            std::lock_guard<std::mutex> lock(mpi_mtx);
            MPI_Send(&msg, sizeof(UpdateMessage), MPI_BYTE, owner, TAG_WRITE_REQ, MPI_COMM_WORLD);
        }
    }

    // --- FIX 2: COMPARE AND EXCHANGE ---
    bool compare_and_exchange(int var_id, int expected, int new_val) {
        if (!isSubscriber(var_id)) return false;

        int owner = getOwner(var_id);

        if (owner == rank) {
            // I am the owner. Handle logic locally.
            bool success = false;
            {
                std::lock_guard<std::mutex> lock(var_mtx);
                if (variables[var_id] == expected) {
                    success = true;
                    // Note: Actual update happens in sendBroadcast to ensure order
                }
            }

            if (success) {
                sendBroadcast(var_id, new_val);
            }
            return success;
        }
        else {
            // Remote Owner
            CASRequest req = { var_id, expected, new_val };
            CASResponse resp;
            MPI_Status status;

            {
                std::lock_guard<std::mutex> lock(mpi_mtx);
                MPI_Send(&req, sizeof(CASRequest), MPI_BYTE, owner, TAG_CAS_REQ, MPI_COMM_WORLD);
                MPI_Recv(&resp, sizeof(CASResponse), MPI_BYTE, owner, TAG_CAS_RESP, MPI_COMM_WORLD, &status);
            }
            return resp.success;
        }
    }

    // --- FIX 3: STOP ---
    void stop() {
        if (!running) return;
        running = false;

        // Use NON-BLOCKING send to self to avoid deadlock
        UpdateMessage dummy;
        MPI_Request req;
        {
            std::lock_guard<std::mutex> lock(mpi_mtx);
            MPI_Isend(&dummy, sizeof(UpdateMessage), MPI_BYTE, rank, TAG_STOP, MPI_COMM_WORLD, &req);
        }
        // We don't wait for this request to finish, just let it fly
        MPI_Request_free(&req);
    }

private:
    void listen() {
        while (running) {
            MPI_Status status;

            // Protect Probe/Recv with mutex if MPI implementation requires it
            {
                // Note: MPI_Probe is blocking, so we release mutex while waiting?
                // Actually, standard Probe blocks. 
                // In a simple lab, we can check Iprobe (non-blocking) in a loop 
                // to allow 'running' flag checks, but Probe is fine for now.
                // We just need to ensure mpi_mtx isn't held forever by others.

                // For safety in this specific lab setup, let's just use Probe 
                // assuming mpi_mtx is only held briefly by senders.
            }

            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            if (status.MPI_TAG == TAG_STOP) break;

            if (status.MPI_TAG == TAG_WRITE_RES) {
                UpdateMessage msg;
                MPI_Recv(&msg, sizeof(UpdateMessage), MPI_BYTE, status.MPI_SOURCE, TAG_WRITE_RES, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                {
                    std::lock_guard<std::mutex> lock(var_mtx);
                    variables[msg.var_id] = msg.value;
                }
                if (onChangeCallback) onChangeCallback(msg.var_id, msg.value);
            }
            else if (status.MPI_TAG == TAG_WRITE_REQ) {
                UpdateMessage msg;
                MPI_Recv(&msg, sizeof(UpdateMessage), MPI_BYTE, status.MPI_SOURCE, TAG_WRITE_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                sendBroadcast(msg.var_id, msg.value);
            }
            else if (status.MPI_TAG == TAG_CAS_REQ) {
                CASRequest req;
                MPI_Recv(&req, sizeof(CASRequest), MPI_BYTE, status.MPI_SOURCE, TAG_CAS_REQ, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                CASResponse resp;
                bool doBroadcast = false;
                {
                    std::lock_guard<std::mutex> lock(var_mtx);
                    if (variables[req.var_id] == req.expected) {
                        resp.success = true;
                        resp.current_value = req.new_value;
                        doBroadcast = true;
                    }
                    else {
                        resp.success = false;
                        resp.current_value = variables[req.var_id];
                    }
                }

                if (doBroadcast) sendBroadcast(req.var_id, req.new_value);

                {
                    std::lock_guard<std::mutex> lock(mpi_mtx);
                    MPI_Send(&resp, sizeof(CASResponse), MPI_BYTE, status.MPI_SOURCE, TAG_CAS_RESP, MPI_COMM_WORLD);
                }
            }
        }
    }

    // --- FIX 4: BROADCAST (Prevent Self-Send) ---
    void sendBroadcast(int var_id, int value) {
        UpdateMessage updateMsg = { var_id, value };
        const auto& targets = subscribers[var_id];

        for (int target_rank : targets) {
            if (target_rank == rank) {
                // LOCAL UPDATE
                {
                    std::lock_guard<std::mutex> lock(var_mtx);
                    variables[var_id] = value;
                }
                if (onChangeCallback) onChangeCallback(var_id, value);
            }
            else {
                // REMOTE UPDATE
                std::lock_guard<std::mutex> lock(mpi_mtx);
                MPI_Send(&updateMsg, sizeof(UpdateMessage), MPI_BYTE, target_rank, TAG_WRITE_RES, MPI_COMM_WORLD);
            }
        }
    }
};

// --- MAIN PROGRAM ---
int main(int argc, char** argv) {
    DSM dsm;
    dsm.init(argc, argv);

    // Setup Callback
    dsm.setCallback([&](int var, int val) {
        std::cout << "[Rank " << dsm.getRank() << "] UPDATE: Var " << var << " -> " << val << std::endl;
        });

    // --- SIMULATION ---
    int rank = dsm.getRank();

    // Ensure all nodes start roughly together
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 3) {
        // Node 0 tries to write to Var 1 (Owned by Node 1)
        std::cout << "Node 3 writing 100 to Var 1" << std::endl;
        dsm.write(1, 100);

        // Wait a bit
        Sleep(1);

        // Try CAS on Var 1 (Expected 100, set to 200)
        bool res = dsm.compare_and_exchange(1, 100, 200);
        std::cout << "Node 3 CAS Result: " << (res ? "Success" : "Fail") << std::endl;
    }
    else if (rank == 1) {
        // Node 1 is the owner of Var 1.
        // It simply listens. 
        // Let's try to interfere after a delay
        Sleep(2);
        dsm.write(1, 300);
    }

    // Keep alive to receive messages
    Sleep(5);

    return 0;
}