#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	//BC=WC=Theta(1)
	//TC=Theta(1)
	this->current_position = 0;
}

void SMIterator::first(){
	//BC=WC=Theta(1)
	//TC=Theta(1)
	this->current_position = 0;
}

void SMIterator::next(){
	//BC=WC=Theta(1)
	//TC=Theta(1)
	if (this->current_position == this->map.size())
		throw exception();
	this->current_position++;
}

bool SMIterator::valid() const{
	//BC=WC=Theta(1)
	//TC=Theta(1)
	return this->current_position < this->map.size();
}

TElem SMIterator::getCurrent() const{
	//BC=WC=Theta(1)
	//TC=Theta(1)
	if (this->current_position == this->map.size())
		throw exception();
	return this->map.elements[this->current_position];
}