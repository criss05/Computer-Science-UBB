#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>

using LongInt = long long;
using VectorType = std::vector<LongInt>;

const int BASE = 10;

// --- UTILITY FUNCTIONS ---
void trim(VectorType& P) {
    while (P.size() > 1 && P.back() == 0) {
        P.pop_back();
    }
}

void normalize(VectorType& C) {
    LongInt carry = 0;
    for (size_t i = 0; i < C.size() || carry > 0; ++i) {
        if (i == C.size()) C.push_back(0);
        LongInt current = C[i] + carry;
        C[i] = current % BASE;
        carry = current / BASE;
    }
    trim(C);
}

VectorType add(const VectorType& A, const VectorType& B) {
    size_t n = std::max(A.size(), B.size());
    VectorType C(n, 0);
    for (size_t i = 0; i < n; ++i) {
        LongInt a = (i < A.size()) ? A[i] : 0;
        LongInt b = (i < B.size()) ? B[i] : 0;
        C[i] = a + b;
    }
    return C;
}

VectorType sub(const VectorType& A, const VectorType& B) {
    size_t n = std::max(A.size(), B.size());
    VectorType C(n, 0);
    for (size_t i = 0; i < n; ++i) {
        LongInt a = (i < A.size()) ? A[i] : 0;
        LongInt b = (i < B.size()) ? B[i] : 0;
        C[i] = a - b;
    }
    return C;
}

VectorType mul_on2_seq(const VectorType& A, const VectorType& B) {
    size_t n = A.size() + B.size() - 1;
    VectorType C(n, 0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            C[i + j] += A[i] * B[j];
        }
    }
    return C;
}

VectorType mul_karatsuba_seq(const VectorType& A, const VectorType& B) {
    size_t n = std::max(A.size(), B.size());
    if (n <= 32) return mul_on2_seq(A, B);

    size_t k = n / 2;

    VectorType A0(A.begin(), A.begin() + std::min(k, A.size()));
    VectorType A1(A.begin() + std::min(k, A.size()), A.end());
    VectorType B0(B.begin(), B.begin() + std::min(k, B.size()));
    VectorType B1(B.begin() + std::min(k, B.size()), B.end());

    if (A1.empty()) return mul_karatsuba_seq(A0, B);
    if (B1.empty()) return mul_karatsuba_seq(A, B0);

    VectorType Z0 = mul_karatsuba_seq(A0, B0);
    VectorType Z2 = mul_karatsuba_seq(A1, B1);
    VectorType Z1 = mul_karatsuba_seq(add(A0, A1), add(B0, B1));

    VectorType Z_mid = sub(sub(Z1, Z0), Z2);

    VectorType C(A.size() + B.size() - 1, 0);

    for (size_t i = 0; i < Z0.size(); ++i)
        if (i < C.size()) C[i] += Z0[i];

    for (size_t i = 0; i < Z_mid.size(); ++i)
        if (i + k < C.size()) C[i + k] += Z_mid[i];

    for (size_t i = 0; i < Z2.size(); ++i)
        if (i + 2 * k < C.size()) C[i + 2 * k] += Z2[i];

    return C;
}

// --- MPI DISTRIBUTED ALGORITHMS ---
VectorType mul_on2_mpi(const VectorType& A, const VectorType& B, int rank, int n_procs) {
    int n_A = A.size();
    int n_B = B.size();

    MPI_Bcast(&n_A, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_B, 1, MPI_INT, 0, MPI_COMM_WORLD);

    VectorType local_B(n_B);
    if (rank == 0) local_B = B;

    MPI_Bcast(local_B.data(), n_B, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    int base_chunk = n_A / n_procs;
    int remainder = n_A % n_procs;

    int my_chunk_size = base_chunk + (rank < remainder ? 1 : 0);
    VectorType local_A(my_chunk_size);

    std::vector<int> sendcounts(n_procs);
    std::vector<int> displs(n_procs);

    if (rank == 0) {
        int offset = 0;
        for (int i = 0; i < n_procs; ++i) {
            sendcounts[i] = base_chunk + (i < remainder ? 1 : 0);
            displs[i] = offset;
            offset += sendcounts[i];
        }
    }

    MPI_Scatterv(rank == 0 ? A.data() : nullptr, sendcounts.data(), displs.data(), MPI_LONG_LONG,
        local_A.data(), my_chunk_size, MPI_LONG_LONG,
        0, MPI_COMM_WORLD);

    VectorType local_res = mul_on2_seq(local_A, local_B);

    int total_size = n_A + n_B - 1;
    VectorType full_local_res(total_size, 0);

    int my_offset = 0;

    int temp_off = 0;
    for (int i = 0; i < rank; ++i) {
        temp_off += base_chunk + (i < remainder ? 1 : 0);
    }
    my_offset = temp_off;

    for (size_t i = 0; i < local_res.size(); ++i) {
        if (my_offset + i < total_size) {
            full_local_res[my_offset + i] = local_res[i];
        }
    }

    VectorType global_res;
    if (rank == 0) global_res.resize(total_size);

    MPI_Reduce(full_local_res.data(), global_res.data(), total_size, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) trim(global_res);
    return global_res;
}

// 2. Distributed Karatsuba (Level 1 Parallelism)
VectorType mul_karatsuba_mpi(const VectorType& A, const VectorType& B, int rank, int n_procs) {
    if (n_procs < 3) {
        if (rank == 0) return mul_karatsuba_seq(A, B);
        else return {};
    }

    const int TAG_A = 1;
    const int TAG_B = 2;
    const int TAG_RES = 3;

    if (rank == 0) {
        size_t n = std::max(A.size(), B.size());
        size_t k = n / 2;

        VectorType A0(A.begin(), A.begin() + std::min(k, A.size()));
        VectorType A1(A.begin() + std::min(k, A.size()), A.end());
        VectorType B0(B.begin(), B.begin() + std::min(k, B.size()));
        VectorType B1(B.begin() + std::min(k, B.size()), B.end());

        VectorType Asum = add(A0, A1);
        VectorType Bsum = add(B0, B1);

        int sz_A0 = A0.size(); int sz_B0 = B0.size();
        MPI_Send(&sz_A0, 1, MPI_INT, 1, TAG_A, MPI_COMM_WORLD);
        MPI_Send(A0.data(), sz_A0, MPI_LONG_LONG, 1, TAG_A, MPI_COMM_WORLD);
        MPI_Send(&sz_B0, 1, MPI_INT, 1, TAG_B, MPI_COMM_WORLD);
        MPI_Send(B0.data(), sz_B0, MPI_LONG_LONG, 1, TAG_B, MPI_COMM_WORLD);

        int sz_A1 = A1.size(); int sz_B1 = B1.size();
        MPI_Send(&sz_A1, 1, MPI_INT, 2, TAG_A, MPI_COMM_WORLD);
        MPI_Send(A1.data(), sz_A1, MPI_LONG_LONG, 2, TAG_A, MPI_COMM_WORLD);
        MPI_Send(&sz_B1, 1, MPI_INT, 2, TAG_B, MPI_COMM_WORLD);
        MPI_Send(B1.data(), sz_B1, MPI_LONG_LONG, 2, TAG_B, MPI_COMM_WORLD);

        VectorType Z1 = mul_karatsuba_seq(Asum, Bsum);

        MPI_Status status;
        int sz_Z0;
        MPI_Recv(&sz_Z0, 1, MPI_INT, 1, TAG_RES, MPI_COMM_WORLD, &status);
        VectorType Z0(sz_Z0);
        MPI_Recv(Z0.data(), sz_Z0, MPI_LONG_LONG, 1, TAG_RES, MPI_COMM_WORLD, &status);

        int sz_Z2;
        MPI_Recv(&sz_Z2, 1, MPI_INT, 2, TAG_RES, MPI_COMM_WORLD, &status);
        VectorType Z2(sz_Z2);
        MPI_Recv(Z2.data(), sz_Z2, MPI_LONG_LONG, 2, TAG_RES, MPI_COMM_WORLD, &status);

        VectorType Z_mid = sub(sub(Z1, Z0), Z2);
        VectorType C(A.size() + B.size() - 1, 0);

        for (size_t i = 0; i < Z0.size(); ++i)
            if (i < C.size()) C[i] += Z0[i];
        for (size_t i = 0; i < Z_mid.size(); ++i)
            if (i + k < C.size()) C[i + k] += Z_mid[i];
        for (size_t i = 0; i < Z2.size(); ++i)
            if (i + 2 * k < C.size()) C[i + 2 * k] += Z2[i];

        trim(C);
        return C;
    }
    else if (rank == 1 || rank == 2) {
        MPI_Status status;
        int sz_A, sz_B;

        MPI_Recv(&sz_A, 1, MPI_INT, 0, TAG_A, MPI_COMM_WORLD, &status);
        VectorType local_A(sz_A);
        MPI_Recv(local_A.data(), sz_A, MPI_LONG_LONG, 0, TAG_A, MPI_COMM_WORLD, &status);

        MPI_Recv(&sz_B, 1, MPI_INT, 0, TAG_B, MPI_COMM_WORLD, &status);
        VectorType local_B(sz_B);
        MPI_Recv(local_B.data(), sz_B, MPI_LONG_LONG, 0, TAG_B, MPI_COMM_WORLD, &status);

        VectorType local_res = mul_karatsuba_seq(local_A, local_B);

        int sz_res = local_res.size();
        MPI_Send(&sz_res, 1, MPI_INT, 0, TAG_RES, MPI_COMM_WORLD);
        MPI_Send(local_res.data(), sz_res, MPI_LONG_LONG, 0, TAG_RES, MPI_COMM_WORLD);

        return {};
    }

    return {};
}


// --- MAIN EXECUTION ---

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int N_POLY = 10000;
    const int N_BIG = 10000;

    VectorType A, B, A_big, B_big;

    if (rank == 0) {
        std::srand(std::time(0));
        A.resize(N_POLY);
        B.resize(N_POLY);
        for (int i = 0; i < N_POLY; ++i) { A[i] = i % 10; B[i] = (i % 5) + 1; }

        A_big.resize(N_BIG);
        B_big.resize(N_BIG);
        for (int i = 0; i < N_BIG; ++i) { A_big[i] = rand() % 10; B_big[i] = rand() % 10; }
    }

    // --- TASK 1: POLYNOMIALS ---
    if (rank == 0) std::cout << "--- POLYNOMIAL MULTIPLICATION (N=" << N_POLY << ") ---" << std::endl;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    VectorType C_on2 = mul_on2_mpi(A, B, rank, size);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double end_time = MPI_Wtime();
        std::cout << "MPI O(n^2) Time: " << std::fixed << std::setprecision(4) << (end_time - start_time) << " s" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    VectorType C_kara = mul_karatsuba_mpi(A, B, rank, size);

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        double end_time = MPI_Wtime();
        std::cout << "MPI Karatsuba Time: " << (end_time - start_time) << " s" << std::endl;

        if (C_on2 == C_kara) std::cout << "Result Validation: MATCH" << std::endl;
        else std::cout << "Result Validation: MISMATCH" << std::endl;
    }


    // --- TASK 2: BIG NUMBERS (BONUS) ---
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) std::cout << "\n--- BIG NUMBER MULTIPLICATION (N=" << N_BIG << ") ---" << std::endl;

    start_time = MPI_Wtime();
    VectorType C_big = mul_on2_mpi(A_big, B_big, rank, size);
    if (rank == 0) {
        normalize(C_big);
        double end_time = MPI_Wtime();
        std::cout << "MPI O(n^2) BigNum Time: " << (end_time - start_time) << " s" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    VectorType C_big_kara = mul_karatsuba_mpi(A_big, B_big, rank, size);
    if (rank == 0) {
        normalize(C_big_kara);
        double end_time = MPI_Wtime();
        std::cout << "MPI Karatsuba BigNum Time: " << (end_time - start_time) << " s" << std::endl;

        if (C_big == C_big_kara) std::cout << "Result Validation: MATCH" << std::endl;
        else std::cout << "Result Validation: MISMATCH" << std::endl;
    }

    MPI_Finalize();
    return 0;
}