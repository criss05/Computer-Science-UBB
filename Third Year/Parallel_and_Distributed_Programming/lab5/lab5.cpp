#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>

using Polynomial = std::vector<long long>;
using namespace std::chrono;

const int NUM_THREADS = 8;


void pad_poly(Polynomial& P, size_t N) {
    if (P.size() < N) {
        P.resize(N, 0);
    }
}

Polynomial poly_add(const Polynomial& A, const Polynomial& B) {
    size_t max_size = std::max(A.size(), B.size());
    Polynomial C(max_size, 0);
    for (size_t i = 0; i < max_size; ++i) {
        long long a = (i < A.size()) ? A[i] : 0;
        long long b = (i < B.size()) ? B[i] : 0;
        C[i] = a + b;
    }
    return C;
}

Polynomial poly_sub(const Polynomial& A, const Polynomial& B) {
    size_t max_size = std::max(A.size(), B.size());
    Polynomial C(max_size, 0);
    for (size_t i = 0; i < max_size; ++i) {
        long long a = (i < A.size()) ? A[i] : 0;
        long long b = (i < B.size()) ? B[i] : 0;
        C[i] = a - b;
    }
    return C;
}

void trim_poly(Polynomial& P) {
    while (P.size() > 1 && P.back() == 0) {
        P.pop_back();
    }
}

// --- 1. O(n^2) SEQUENTIAL ---
Polynomial O_n2_Sequential(const Polynomial& A, const Polynomial& B) {
    size_t size_C = A.size() + B.size() - 1;
    Polynomial C(size_C, 0);

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            C[i + j] += A[i] * B[j];
        }
    }
    trim_poly(C);
    return C;
}

// --- 2. O(n^2) PARALLEL HELPER ---
struct ThreadData {
    const Polynomial* A;
    const Polynomial* B;
    size_t start_i;
    size_t end_i;
    Polynomial C_local;
};

void n2_worker(ThreadData* data) {
    size_t size_C = data->A->size() + data->B->size() - 1;
    data->C_local.resize(size_C, 0);

    for (size_t i = data->start_i; i < data->end_i; ++i) {
        for (size_t j = 0; j < data->B->size(); ++j) {
            data->C_local[i + j] += (*data->A)[i] * (*data->B)[j];
        }
    }
}

// --- 2. O(n^2) PARALLEL MAIN ---
Polynomial O_n2_Parallel(const Polynomial& A, const Polynomial& B) {
    size_t size_C = A.size() + B.size() - 1;
    Polynomial C(size_C, 0);

    int num_threads = std::min((int)NUM_THREADS, (int)A.size());
    if (num_threads == 0) return Polynomial(1, 0);

    std::vector<std::thread> workers;
    std::vector<ThreadData> data(num_threads);

    size_t chunk_size = A.size() / num_threads;

    for (int k = 0; k < num_threads; ++k) {
        data[k].A = &A;
        data[k].B = &B;
        data[k].start_i = k * chunk_size;
        data[k].end_i = (k == num_threads - 1) ? A.size() : (k + 1) * chunk_size;

        workers.emplace_back(n2_worker, &data[k]);
    }

    for (auto& t : workers) {
        t.join();
    }

    for (int k = 0; k < num_threads; ++k) {
        for (size_t i = 0; i < size_C; ++i) {
            C[i] += data[k].C_local[i];
        }
    }

    trim_poly(C);
    return C;
}

// --- 3. KARATSUBA SEQUENTIAL ---

Polynomial karatsuba_sequential_impl(const Polynomial& A, const Polynomial& B) {
    size_t n = std::max(A.size(), B.size());

    if (n <= 32) {
        return O_n2_Sequential(A, B);
    }

    size_t N = 1;
    while (N < n) N <<= 1;

    Polynomial P_A = A;
    Polynomial P_B = B;
    pad_poly(P_A, N);
    pad_poly(P_B, N);

    size_t m = N / 2;

    Polynomial A0(P_A.begin(), P_A.begin() + m);
    Polynomial A1(P_A.begin() + m, P_A.end());
    Polynomial B0(P_B.begin(), P_B.begin() + m);
    Polynomial B1(P_B.begin() + m, P_B.end());

    Polynomial Z0 = karatsuba_sequential_impl(A0, B0);
    Polynomial Z2 = karatsuba_sequential_impl(A1, B1);

    Polynomial sum_A = poly_add(A0, A1);
    Polynomial sum_B = poly_add(B0, B1);
    Polynomial Z1 = karatsuba_sequential_impl(sum_A, sum_B);

    Polynomial Z_mid = poly_sub(poly_sub(Z1, Z2), Z0);

    Polynomial C(2 * N, 0);

    for (size_t i = 0; i < Z0.size(); ++i) C[i] += Z0[i];

    for (size_t i = 0; i < Z_mid.size(); ++i) C[i + m] += Z_mid[i];

    for (size_t i = 0; i < Z2.size(); ++i) C[i + N] += Z2[i];

    
    return C;
}

Polynomial Karatsuba_Sequential(const Polynomial& A, const Polynomial& B) {
    Polynomial C =  karatsuba_sequential_impl(A, B);
    trim_poly(C);
    return C;
}

// --- 4. KARATSUBA PARALLEL ---
Polynomial karatsuba_parallel_impl(const Polynomial& A, const Polynomial& B, int depth) {
    size_t n = std::max(A.size(), B.size());

    if (n <= 32) {
        return O_n2_Sequential(A, B);
    }

    if (depth > std::log2(NUM_THREADS)) {
        return karatsuba_sequential_impl(A, B);
    }

    size_t N = 1;
    while (N < n) N <<= 1;

    Polynomial P_A = A;
    Polynomial P_B = B;
    pad_poly(P_A, N);
    pad_poly(P_B, N);

    size_t m = N / 2;

    Polynomial A0(P_A.begin(), P_A.begin() + m);
    Polynomial A1(P_A.begin() + m, P_A.end());
    Polynomial B0(P_B.begin(), P_B.begin() + m);
    Polynomial B1(P_B.begin() + m, P_B.end());

    Polynomial Z0, Z1, Z2;

    Polynomial sum_A = poly_add(A0, A1);
    Polynomial sum_B = poly_add(B0, B1);

    std::thread t0([&]() { Z0 = karatsuba_parallel_impl(A0, B0, depth + 1); });
    std::thread t2([&]() { Z2 = karatsuba_parallel_impl(A1, B1, depth + 1); });

    Z1 = karatsuba_parallel_impl(sum_A, sum_B, depth + 1);

    t0.join();
    t2.join();

    Polynomial Z_mid = poly_sub(poly_sub(Z1, Z2), Z0);
    Polynomial C(2 * N, 0);

    for (size_t i = 0; i < Z0.size(); ++i) C[i] += Z0[i];
    for (size_t i = 0; i < Z_mid.size(); ++i) C[i + m] += Z_mid[i];
    for (size_t i = 0; i < Z2.size(); ++i) C[i + N] += Z2[i];


    return C;
}

Polynomial Karatsuba_Parallel(const Polynomial& A, const Polynomial& B) {
    Polynomial C = karatsuba_parallel_impl(A, B, 0);
    trim_poly(C);
    return C;
}

// --- MAIN EXECUTION AND TIMING ---
void run_and_measure(const std::string& name,
    Polynomial(*algo_func)(const Polynomial&, const Polynomial&),
    const Polynomial& A, const Polynomial& B,
    const Polynomial& reference_result) {

    std::cout << std::left << std::setw(25) << name << ": ";

    auto start = high_resolution_clock::now();
    Polynomial C = algo_func(A, B);
    auto stop = high_resolution_clock::now();

    std::chrono::duration<double> duration = stop - start;
    double time_ms = duration.count();

    bool correct = (C == reference_result);
    std::cout << std::fixed << std::setprecision(4) << time_ms << " s";
    if (!correct) std::cout << " (ERROR: Result Mismatch!)";
    std::cout << std::endl;
}

int main() {
    std::cout << "--- Polynomial Multiplication Comparison (Threads: " << NUM_THREADS << ") ---" << std::endl;
    const size_t N2 = 20000;
    Polynomial A2(N2);
    Polynomial B2(N2);

    std::srand(std::time(0));
    for (size_t i = 0; i < N2; ++i) {
        A2[i] = std::rand() % 10;
        B2[i] = std::rand() % 10;
    }

    std::cout << "\nCalculating Reference (Normal Sequential)" << std::endl;
    auto start_ref = high_resolution_clock::now();
    Polynomial ref_result2 = O_n2_Sequential(A2, B2);
    auto stop_ref = high_resolution_clock::now();
    std::chrono::duration<double> duration = stop_ref - start_ref;
    double time_ref_ms = duration.count();

    std::cout << std::left << std::setw(25) << "Normal Sequential (Ref)" << ": ";
    std::cout << "[Result used for verification] - " << std::fixed << std::setprecision(4) << time_ref_ms << " s" << std::endl;


    run_and_measure("Normal Parallel", O_n2_Parallel, A2, B2, ref_result2);
    run_and_measure("Karatsuba Sequential", Karatsuba_Sequential, A2, B2, ref_result2);
    run_and_measure("Karatsuba Parallel", Karatsuba_Parallel, A2, B2, ref_result2);

    std::cout << "\n--- Execution Complete ---" << std::endl;

    return 0;
}