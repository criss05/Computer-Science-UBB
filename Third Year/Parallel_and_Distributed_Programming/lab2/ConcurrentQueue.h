#pragma once
#include <mutex>
#include <condition_variable>

class ConcurrentQueue
{
private: 
	int size;
	int capacity;
	int* elements;
	std::mutex mutex;
	std::condition_variable can_consume;
	std::condition_variable can_produce;

public:
	ConcurrentQueue(int cap);
	~ConcurrentQueue();

	void push(int element);
	void pop();

	int front();
};



