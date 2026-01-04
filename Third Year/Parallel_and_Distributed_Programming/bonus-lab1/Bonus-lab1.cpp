#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "DoublyLinkedList.h"

using namespace std;

void printListForward(DLL& list) {
    Node* current = list.getHead();
    cout << "List (forward): ";
    while (current) {
        cout << current->getValue() << " ";
        current = current->getNext();
    }
    cout << endl;
}

void printListBackward(DLL& list) {
    Node* current = list.getTail();
    cout << "List (backward): ";
    while (current) {
        cout << current->getValue() << " ";
        current = current->getPrev();
    }
    cout << endl;
}

void concurrentInsertAfter(DLL& list, Node* start, int threadId) {
    Node* current = start;
    for (int i = 0; i < 3; i++) {
        current = list.insertAfter(current, threadId * 10 + i);
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void concurrentInsertBefore(DLL& list, Node* start, int threadId) {
    Node* current = start;
    for (int i = 0; i < 3; i++) {
        current = list.insertBefore(current, threadId * 100 + i);
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    Node* n1 = new Node(1);
    Node* n2 = new Node(2, n1);
    Node* n3 = new Node(3, n2);
    n1->setNext(n2);
    n2->setNext(n3);

    DLL list(n1);
    list.setTail(n3);

    cout << "Initial list:" << endl;
    printListForward(list);
    printListBackward(list);

    const int numThreads = 10000;
    vector<thread> threads;
    threads.reserve(numThreads);

    for (int i = 0; i < numThreads; i++) {
        if (i % 2) {
            threads.emplace_back([&list, n1, i]() {
                list.insertAfter(n1, 100000 + i);
                this_thread::sleep_for(chrono::milliseconds(10));
             });
        }
        else {
            threads.emplace_back([&list, n3, i]() {
                list.insertBefore(n3, 100000 + i);
                this_thread::sleep_for(chrono::milliseconds(10));
             });
        }
        
    }

    for (auto& t : threads)
        t.join();

    cout << "\nAfter concurrent operations:" << endl;
    printListForward(list);
    printListBackward(list);

    cout << "\nConsistency check (forward -> backward):" << endl;
    Node* forward = list.getHead();
    Node* backward = list.getTail();
    int forwardCount = 0, backwardCount = 0;

    while (forward) { forwardCount++; forward = forward->getNext(); }
    while (backward) { backwardCount++; backward = backward->getPrev(); }

    cout << "Forward count = " << forwardCount << ", Backward count = " << backwardCount << endl;
    if (forwardCount == backwardCount)
        cout << "List is consistent." << endl;
    else
        cout << "Inconsistency detected!" << endl;

    return 0;
}
