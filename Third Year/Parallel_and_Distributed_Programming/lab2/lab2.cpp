#include <iostream>
#include <thread>
#include <vector>
#include "ConcurrentQueue.h"
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

int cap = 1000;
ConcurrentQueue* queue = new ConcurrentQueue{cap};
int result;

int s = 1000;
vector<int> v1(s);
vector<int> v2(s);

void GenerateVector() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10, 100);

    for (int i = 0; i < s; i++) {
        v1[i] = dis(gen);
        v2[i] = dis(gen);
    }
}

int check() {
    int result = 0;
    for (int i = 0; i < s; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

void sum() 
{
    for (int i = 0; i < s; i++) {
        int element = queue->front();
        queue->pop();
        result += element;
   }
}

void product() 
{
    for (int i = 0; i < s; i++) {
        int prod = v1[i] * v2[i];
        queue->push(prod);
    }
}

int main()
{
    GenerateVector();

    auto start = high_resolution_clock::now();

    thread producer(product);
    thread consumer(sum);

    producer.join();
    consumer.join();

    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;

    cout << "Concurrent result: " << result << "\n";
    cout << "Sequential result: " << check() << "\n";
    cout << "Execution time (threads): " << duration.count() << " ms\n";
}

