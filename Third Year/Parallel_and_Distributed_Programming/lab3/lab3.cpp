#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

int common = 10;
int rows1 = 10;
int cols2 = 10;
int thread_count = 4;

vector<vector<int>> matrix1(rows1, vector<int>(common));
vector<vector<int>> matrix2(common, vector<int>(cols2));
vector<vector<int>> result(rows1, vector<int>(cols2));

void generateMatrix() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 100);

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < common; j++) {
            matrix1[i][j] = dis(gen);
        }
    }

    for (int i = 0; i < common; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = dis(gen);
        }
    }
}

int compute_element(int i, int j) {
    int number = 0;
    for (int k = 0; k < common; k++) {
        number += matrix1[i][k] * matrix2[k][j];
    }
    return number;
}

void check() {
    int elem;
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            elem = compute_element(i, j);
            if (result[i][j] != elem) {
                cout << "Matrices do not match\n";
                return;
            }
        }
    }
}

void move_rows(int thread_index) {
    int elems_per_thread = (rows1 * cols2) / thread_count;
    int start_elem = elems_per_thread * (thread_index);
    int start_row = start_elem / cols2;
    int start_col = start_elem % cols2;
    
    if (thread_index == thread_count - 1) {
        elems_per_thread += (rows1 * cols2) % thread_count;
    }

    while (elems_per_thread) {
        result[start_row][start_col] = compute_element(start_row, start_col);

        if (start_col == cols2 - 1) {
            start_row++;
            start_col = 0;
        }
        else {
            start_col++;
        }
        elems_per_thread--;

        cout << "Thread: " << thread_index << "->(" << start_row << ", " << start_col << ")" << endl;
    }
}

void move_columns(int thread_index) {
    int elems_per_thread = (rows1 * cols2) / thread_count;
    int start_elem = elems_per_thread * (thread_index);
    int start_row = start_elem / rows1;
    int start_col = start_elem % rows1;

    if (thread_index == thread_count - 1) {
        elems_per_thread += (rows1 * cols2) % thread_count;
    }

    while (elems_per_thread) {
        result[start_row][start_col] = compute_element(start_row, start_col);

        if (start_col == cols2 - 1) {
            start_row++;
            start_col = 0;
        }
        else {
            start_col++;
        }
        elems_per_thread--;

        cout << "Thread: " << thread_index << "->(" << start_row << ", " << start_col << ")" << endl;
    }
}

void move_element(int thread_index) {
    int total_elems = rows1 * cols2;

    for (int i = thread_index; i < total_elems; i += thread_count) {
        int row = i / cols2;
        int column = i % cols2;

        result[row][column] = compute_element(row, column);

        cout << "Thread: " << thread_index << "->(" << row << ", " << column << ")" << endl;
    }
}

int main()
{
    generateMatrix();

    auto start = high_resolution_clock::now();

    vector<thread> threads;
    for (int i = 0; i < thread_count; i++) {
        //threads.emplace_back(move_rows, i);
        //threads.emplace_back(move_columns, i);
        threads.emplace_back(move_element, i);
    }

    for (int i = 0; i < thread_count; i++) {
        threads[i].join();
    }

    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;

    check();
    cout << "\nMatrices match;\n";
    cout << "Execution time (threads): " << duration.count() << " ms\n";
    /*for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }*/
}