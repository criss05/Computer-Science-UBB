#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

void SortedBag::resize(){
	this->capacity = this->capacity * 2;
	Node* new_nodes = new Node[this->capacity];
	for (int i = 0; i < this->capacity/2; i++)
		new_nodes[i] = this->nodes[i];
	delete[] this->nodes;
	this->nodes = new_nodes;

	for (int i = this->capacity/2; i < this->capacity; i++) {
		if (i == this->capacity/2)
			this->nodes[i].SetPrev(-1);
		else
			this->nodes[i].SetPrev(i - 1);
		this->nodes[i].SetNext(i + 1);
	}
	this->firstEmpty = this->capacity/2;
	this->nodes[this->capacity - 1].SetNext(-1);
}

void SortedBag::free_pos(int position){
	this->nodes[position].SetNext(this->firstEmpty);
	this->nodes[position].SetPrev(-1);
	if (this->firstEmpty != -1)
		this->nodes[this->firstEmpty].SetPrev(position);
	this->firstEmpty = position;
}

int SortedBag::allocate_pos(){
	int newElem = this->firstEmpty;
	if (newElem != -1) {
		this->firstEmpty = this->nodes[this->firstEmpty].next();
		if (this->firstEmpty != -1)
			this->nodes[this->firstEmpty].SetPrev(-1);
		this->nodes[newElem].SetNext(-1);
		this->nodes[newElem].SetPrev(-1);
	}
	return newElem;
}

SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->capacity = 10;
	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
	this->bag_size = 0;
	this->nodes = new Node[this->capacity];

	for (int i = 0; i < this->capacity; i++)
	{
		this->nodes[i].SetPrev(i - 1);
		this->nodes[i].SetNext(i + 1);
	}
	this->nodes[this->capacity-1].SetNext(-1);
}

void SortedBag::add(TComp e) {
	int current = this->head;
	while(current != -1 && this->relation(this->nodes[current].element(), e) && this->nodes[current].element() != e) {
		current = this->nodes[current].next();
	}
	if (current == -1) {
		int newNode = this->allocate_pos();
		if (newNode == -1) {
			this->resize();
			newNode = this->allocate_pos();
		}
		this->nodes[newNode].SetElement(e);
		this->nodes[newNode].SetFrequency(1);

		if (this->head == -1) {
			this->tail = newNode;
			this->head = newNode;
		}
		else {
			this->nodes[this->tail].SetNext(newNode);
			this->nodes[newNode].SetPrev(this->tail);
			this->tail = newNode;
		}
	}
	else {
		
		if (this->nodes[current].element() == e)
			this->nodes[current].SetFrequency(this->nodes[current].frequency() + 1);
		else {
			int newNode = this->allocate_pos();
			if (newNode == -1) {
				this->resize();
				newNode = this->allocate_pos();
			}
			this->nodes[newNode].SetElement(e);
			this->nodes[newNode].SetFrequency(1);
			if(current == this->head){
				this->nodes[head].SetPrev(newNode);
				this->nodes[newNode].SetNext(this->head);
				this->head = newNode;
			}
			else {
				int prev = this->nodes[current].prev();
				this->nodes[prev].SetNext(newNode);
				this->nodes[newNode].SetPrev(prev);
				this->nodes[current].SetPrev(newNode);
				this->nodes[newNode].SetNext(current);
			}
		}
	}
	this->bag_size++;
}


bool SortedBag::remove(TComp e) {
	int current = this->head;
	while (current != -1 && this->nodes[current].element() != e) {
		current = this->nodes[current].next();
		if (this->relation(this->nodes[current].element(), e) == false)
			return false;
	}
	if (current == -1)
		return false;
	else {
		int prev = this->nodes[current].prev();
		int next = this->nodes[current].next();
		if (prev == -1 && next == -1) {
			if (this->nodes[current].frequency() == 1) {
				this->free_pos(current);
				this->head = -1;
				this->tail = -1;
			}
			else
				this->nodes[current].SetFrequency(this->nodes[current].frequency() - 1);
			this->bag_size --;
		}
		if (prev == -1 && next != -1) {
			if (this->nodes[current].frequency() == 1) {
				this->head = next;
				this->nodes[this->head].SetPrev(-1);
				this->free_pos(current);
			}
			else
				this->nodes[current].SetFrequency(this->nodes[current].frequency() - 1);

			this->bag_size--;
		}
		if (prev != -1 && next == -1) {
			if (this->nodes[current].frequency() == 1) {
				this->tail = prev;
				this->nodes[this->tail].SetNext(-1);
				this->free_pos(current);
			}
			else
				this->nodes[current].SetFrequency(this->nodes[current].frequency() - 1);

			this->bag_size--;
		}
		if (prev != -1 && next != -1) {
			if (this->nodes[current].frequency() == 1) {
				this->nodes[prev].SetNext(next);
				this->nodes[next].SetPrev(prev);
				this->free_pos(current);
			}
			else
				this->nodes[current].SetFrequency(this->nodes[current].frequency() - 1);
			this->bag_size--;
		}
	}
	return true;
}


bool SortedBag::search(TComp elem) const {
	int current = this->head;
	while (current != -1) {
		if (this->nodes[current].element() == elem)
			return true;
		if (this->relation(this->nodes[current].element(), elem) == false)
			return false;
		current = this->nodes[current].next();

	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	int current = this->head;
	while (current != -1) {
		if (this->nodes[current].element() == elem)
			return this->nodes[current].frequency();
		if (this->relation(this->nodes[current].element(), elem) == false)
			return 0;
		current = this->nodes[current].next();
		
	}
	return 0;
}



int SortedBag::size() const {
	return this->bag_size;
}


bool SortedBag::isEmpty() const {
	return this->bag_size == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	delete this->nodes;
}
