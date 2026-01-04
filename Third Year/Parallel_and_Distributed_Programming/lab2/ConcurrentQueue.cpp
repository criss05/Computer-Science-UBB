#include "ConcurrentQueue.h"

using namespace std;

ConcurrentQueue::ConcurrentQueue(int cap)
{
	this->capacity = cap;
	this->size = 0;
	this->elements = new int[capacity];
}

ConcurrentQueue::~ConcurrentQueue()
{
	delete[] elements;
}

void ConcurrentQueue::push(int element)
{
	std::unique_lock<std::mutex> lock(this->mutex);

	this->can_produce.wait(lock, [this]() { return size < capacity; });

	this->elements[size++] = element;
	
	this->can_consume.notify_one();
}

void ConcurrentQueue::pop()
{
	std::unique_lock<std::mutex> lock(this->mutex);

	this->can_consume.wait(lock, [this]() { return size > 0; });

	for (int i = 0; i < size - 1; i++) {
		this->elements[i] = this->elements[i + 1];
	}
	this->elements[--size] = NULL;

	can_produce.notify_one();
}

int ConcurrentQueue::front()
{
	std::unique_lock<std::mutex> lock(this->mutex);

	this->can_consume.wait(lock, [this]() { return size > 0; });

	return this->elements[0];
}
