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

// Define BigNumber as a vector of digits (least significant digit first)
using BigNumber = std::vector<long long>;
using namespace std::chrono;

const int NUM_THREADS = 8;
const int BASE = 10; // Base for carries (each element is a digit 0-9)


// ------------------------------------------------------------------------
// I. CORE UTILITY FUNCTIONS (Adapted Naming)
// ------------------------------------------------------------------------

void pad_number(BigNumber& P, size_t N) {
    if (P.size() < N) {
        P.resize(N, 0);
    }
}

BigNumber big_add(const BigNumber& A, const BigNumber& B) {
    size_t max_size = std::max(A.size(), B.size());
    BigNumber C(max_size, 0);
    for (size_t i = 0; i < max_size; ++i) {
        long long a = (i < A.size()) ? A[i] : 0;
        long long b = (i < B.size()) ? B[i] : 0;
        C[i] = a + b;
    }
    return C;
}

BigNumber big_sub(const BigNumber& A, const BigNumber& B) {
    size_t max_size = std::max(A.size(), B.size());
    BigNumber C(max_size, 0);
    for (size_t i = 0; i < max_size; ++i) {
        long long a = (i < A.size()) ? A[i] : 0;
        long long b = (i < B.size()) ? B[i] : 0;
        C[i] = a - b;
    }
    return C;
}

void trim_number(BigNumber& P) {
    while (P.size() > 1 && P.back() == 0) {
        P.pop_back();
    }
}

// NEW UTILITY: NORMALIZATION (Handling Carries - Essential for Big Numbers)
void normalize(BigNumber& C) {
    long long carry = 0;
    size_t size_C = C.size();

    for (size_t i = 0; i < size_C || carry > 0; ++i) {
        if (i >= size_C) {
            C.push_back(0);
            size_C++;
        }

        long long current_value = C[i] + carry;
        C[i] = current_value % BASE;
        carry = current_value / BASE;
    }
    trim_number(C);
}

void print_big_number(const BigNumber& B) {
    if (B.empty()) { std::cout << "0"; return; }

    // Print digits from most significant (back) to least significant (front)
    for (int i = B.size() - 1; i >= 0; --i) {
        std::cout << B[i];
    }
}


// ----------------------------------------------------------------------
// II. BIG NUMBER MULTIPLICATION (ADAPTED ALGORITHMS)
// ----------------------------------------------------------------------

// Forward declarations for Karatsuba to use the O(n^2) base case
BigNumber karatsuba_big_sequential_impl(const BigNumber& A, const BigNumber& B);
BigNumber karatsuba_big_parallel_impl(const BigNumber& A, const BigNumber& B, int depth);

// 1. O(n^2) Sequential Big Number
BigNumber BigMul_O_n2_Sequential(const BigNumber& A, const BigNumber& B) {
    size_t size_C = A.size() + B.size() - 1;
    BigNumber C(size_C, 0);

    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            C[i + j] += A[i] * B[j];
        }
    }
    normalize(C);
    return C;
}

// 2. O(n^2) Parallel Helper (Adapted Struct)
struct BigMulThreadData {
    const BigNumber* A;
    const BigNumber* B;
    size_t start_i;
    size_t end_i;
    BigNumber C_local;
};

void big_n2_worker(BigMulThreadData* data) {
    size_t size_C = data->A->size() + data->B->size() - 1;
    data->C_local.resize(size_C, 0);

    for (size_t i = data->start_i; i < data->end_i; ++i) {
        for (size_t j = 0; j < data->B->size(); ++j) {
            data->C_local[i + j] += (*data->A)[i] * (*data->B)[j];
        }
    }
}

// 2. O(n^2) Parallel Big Number
BigNumber BigMul_O_n2_Parallel(const BigNumber& A, const BigNumber& B) {
    size_t size_C = A.size() + B.size() - 1;
    BigNumber C(size_C, 0);

    int num_threads = std::min((int)NUM_THREADS, (int)A.size());
    if (num_threads == 0) return BigNumber(1, 0);

    std::vector<std::thread> workers;
    std::vector<BigMulThreadData> data(num_threads);

    size_t chunk_size = A.size() / num_threads;

    for (int k = 0; k < num_threads; ++k) {
        data[k].A = &A;
        data[k].B = &B;
        data[k].start_i = k * chunk_size;
        data[k].end_i = (k == num_threads - 1) ? A.size() : (k + 1) * chunk_size;

        workers.emplace_back(big_n2_worker, &data[k]);
    }

    for (auto& t : workers) { t.join(); }

    for (int k = 0; k < num_threads; ++k) {
        for (size_t i = 0; i < size_C; ++i) {
            C[i] += data[k].C_local[i];
        }
    }

    normalize(C);
    return C;
}


// 3. Karatsuba Sequential Big Number (Recursive)
BigNumber karatsuba_big_sequential_impl(const BigNumber& A, const BigNumber& B) {
    size_t n = std::max(A.size(), B.size());

    if (n <= 32) return BigMul_O_n2_Sequential(A, B);

    size_t N = 1; while (N < n) N <<= 1;

    BigNumber P_A = A; pad_number(P_A, N);
    BigNumber P_B = B; pad_number(P_B, N);
    size_t m = N / 2;

    BigNumber A0(P_A.begin(), P_A.begin() + m);
    BigNumber A1(P_A.begin() + m, P_A.end());
    BigNumber B0(P_B.begin(), P_B.begin() + m);
    BigNumber B1(P_B.begin() + m, P_B.end());

    BigNumber Z0 = karatsuba_big_sequential_impl(A0, B0);
    BigNumber Z2 = karatsuba_big_sequential_impl(A1, B1);

    BigNumber sum_A = big_add(A0, A1);
    BigNumber sum_B = big_add(B0, B1);
    BigNumber Z1 = karatsuba_big_sequential_impl(sum_A, sum_B);

    BigNumber Z_mid = big_sub(big_sub(Z1, Z2), Z0);
    BigNumber C(2 * N, 0);

    for (size_t i = 0; i < Z0.size(); ++i) C[i] += Z0[i];
    for (size_t i = 0; i < Z_mid.size(); ++i) C[i + m] += Z_mid[i];
    for (size_t i = 0; i < Z2.size(); ++i) C[i + N] += Z2[i];

    normalize(C);
    return C;
}

BigNumber Karatsuba_Big_Sequential(const BigNumber& A, const BigNumber& B) {
    return karatsuba_big_sequential_impl(A, B);
}


// 4. Karatsuba Parallel Big Number (Recursive)
BigNumber karatsuba_big_parallel_impl(const BigNumber& A, const BigNumber& B, int depth) {
    size_t n = std::max(A.size(), B.size());

    if (n <= 32) return BigMul_O_n2_Sequential(A, B);
    if (depth > (int)std::log2(NUM_THREADS)) return karatsuba_big_sequential_impl(A, B);

    size_t N = 1; while (N < n) N <<= 1;

    BigNumber P_A = A; pad_number(P_A, N);
    BigNumber P_B = B; pad_number(P_B, N);
    size_t m = N / 2;

    BigNumber A0(P_A.begin(), P_A.begin() + m);
    BigNumber A1(P_A.begin() + m, P_A.end());
    BigNumber B0(P_B.begin(), P_B.begin() + m);
    BigNumber B1(P_B.begin() + m, P_B.end());

    BigNumber Z0, Z1, Z2;
    BigNumber sum_A = big_add(A0, A1);
    BigNumber sum_B = big_add(B0, B1);

    // Launch threads, recursively calling the Big Number parallel implementation
    std::thread t0([&]() { Z0 = karatsuba_big_parallel_impl(A0, B0, depth + 1); });
    std::thread t2([&]() { Z2 = karatsuba_big_parallel_impl(A1, B1, depth + 1); });

    Z1 = karatsuba_big_parallel_impl(sum_A, sum_B, depth + 1);

    t0.join();
    t2.join();

    BigNumber Z_mid = big_sub(big_sub(Z1, Z2), Z0);
    BigNumber C(2 * N, 0);

    for (size_t i = 0; i < Z0.size(); ++i) C[i] += Z0[i];
    for (size_t i = 0; i < Z_mid.size(); ++i) C[i + m] += Z_mid[i];
    for (size_t i = 0; i < Z2.size(); ++i) C[i + N] += Z2[i];

    normalize(C);
    return C;
}

BigNumber Karatsuba_Big_Parallel(const BigNumber& A, const BigNumber& B) {
    return karatsuba_big_parallel_impl(A, B, 0);
}


// ----------------------------------------------------------------------
// III. MAIN EXECUTION (Testing Big Numbers)
// ----------------------------------------------------------------------

void run_and_measure_big(const std::string& name,
    BigNumber(*algo_func)(const BigNumber&, const BigNumber&),
    const BigNumber& A, const BigNumber& B,
    const BigNumber& reference_result) {

    std::cout << std::left << std::setw(25) << name << ": ";

    auto start = high_resolution_clock::now();
    BigNumber C = algo_func(A, B);
    auto stop = high_resolution_clock::now();

    std::chrono::duration<double> duration = stop - start;
    double time_s = duration.count();

    bool correct = (C == reference_result);

    // Output format for Big Numbers
    std::cout << "[";
    print_big_number(C);
    std::cout << "] - " << std::fixed << std::setprecision(4) << time_s << " s";
    if (!correct) std::cout << " (ERROR: Result Mismatch!)";
    std::cout << std::endl;
}


int main() {
    std::cout << "--- BIG NUMBER MULTIPLICATION (Threads: " << NUM_THREADS << ") ---" << std::endl;
    const size_t N_BIG = 10000;
    BigNumber B_A(N_BIG), B_B(N_BIG);

    std::srand(std::time(0));
    for (size_t i = 0; i < N_BIG; ++i) {
        B_A[i] = std::rand() % 10; // Digits 0-9
        B_B[i] = std::rand() % 10;
    }

    std::cout << "Number of Digits (N): " << N_BIG << std::endl;
    std::cout << "Example Input: "; print_big_number(B_A); std::cout << " x "; print_big_number(B_B); std::cout << std::endl;

    // BIG NUMBER: Reference (Need to use the Big Number sequential version for correctness)
    auto start_ref = high_resolution_clock::now();
    BigNumber ref_result_big = BigMul_O_n2_Sequential(B_A, B_B);
    auto stop_ref = high_resolution_clock::now();
    std::chrono::duration<double> duration_ref = stop_ref - start_ref;

    std::cout << std::left << std::setw(25) << "Normal Sequential (Ref)" << ": ";
    std::cout << "[Result used for verification] - " << duration_ref.count() << " s" << std::endl;


    run_and_measure_big("Normal Parallel", BigMul_O_n2_Parallel, B_A, B_B, ref_result_big);
    run_and_measure_big("Karatsuba Sequential", Karatsuba_Big_Sequential, B_A, B_B, ref_result_big);
    run_and_measure_big("Karatsuba Parallel", Karatsuba_Big_Parallel, B_A, B_B, ref_result_big);

    std::cout << "\n--- Execution Complete ---" << std::endl;

    return 0;
}