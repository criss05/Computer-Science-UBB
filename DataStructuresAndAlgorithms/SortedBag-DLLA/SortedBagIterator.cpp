#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentElement = b.head;
	this->currentFrequency = 1;
}

TComp SortedBagIterator::getCurrent() {
	if (this->currentElement == -1)
		throw exception();
	return this->bag.nodes[this->currentElement].element();
}

bool SortedBagIterator::valid() {
	return this->currentElement != -1;
}

void SortedBagIterator::next() {
	if (this->currentElement == -1)
		throw exception();
	if (this->currentFrequency == this->bag.nodes[this->currentElement].frequency()) {
		this->currentElement = this->bag.nodes[this->currentElement].next();
		this->currentFrequency = 1;
		
	}
	else
	{
		this->currentFrequency++;
	}
}

void SortedBagIterator::first() {
	this->currentElement = this->bag.head;
	this->currentFrequency = 1;
}

