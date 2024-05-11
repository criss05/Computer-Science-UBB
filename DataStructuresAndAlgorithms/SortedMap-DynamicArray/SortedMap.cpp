#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

void SortedMap::resize(int factor){
	//BC=WC =Theta(n)
	//TC = Theta(n)
	this->capacity = this->capacity * factor;
	TElem* copy = new TElem[this->capacity];
	for (int i = 0; i < this->size_map; i++) {
		copy[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = copy;
}

SortedMap::SortedMap(Relation r) {
	//BC=WC=Theta(1)
	//TC=Theta(1)
	this->capacity = 10;
	this->size_map = 0;
	this->elements = new TElem[this->capacity];
	this->relation = r;
}

TValue SortedMap::add(TKey k, TValue v) {
	//BC = Theta(1)
	//WC = Theta(n)
	//TC = O(n)
	if(this->size_map == this->capacity){
		resize();
	}
	int position = 0;
	int count = 0;
	TValue aux = NULL_TVALUE;
	int good_pos = 0;
	while (count < 1 && position < this->size_map) {
		if (this->elements[position].first == k) {
			aux = this->elements[position].second;
			this->elements[position].second = v;
			count++;
		}
		if (this->relation(this->elements[position].first, k)) {
			good_pos = position+1;
		}
		position++;
	}
	TElem t{ k,v };
	if (good_pos <= this->size_map && count == 0) {
		for (int i = this->size_map; i > good_pos; i--) {
			this->elements[i] = this->elements[i - 1];
		}
		this->size_map++;
		this->elements[good_pos] = t;
	}
	return aux;
}

TValue SortedMap::search(TKey k) const {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	int position = 0;
	TValue result = NULL_TVALUE;
	int nrfound = 0;
	while (nrfound<1 && position < this->size_map) {
		if (this->elements[position].first == k) {
			result = this->elements[position].second;
			nrfound++;
		}
		position++;
	}
	return result;
}

TValue SortedMap::remove(TKey k) {
	//BC=WC=Theta(n)
	//TC=Theta(n)
	int position = 0;
	TValue result = NULL_TVALUE;
	while (position < this->size_map && result==NULL_TVALUE) {
		if (this->elements[position].first == k) {
			result = this->elements[position].second;
			for (int i = position; i < this->size_map-1; i++)
				this->elements[i] = this->elements[i + 1];
			this->size_map--;
		}
		position++;
	}
	return result;
}

int SortedMap::size() const {
	//BC=WC=Theta(1)
	//TC=Theta(1)
	return this->size_map;
}

bool SortedMap::isEmpty() const {
	//BC=WC=Theta(1)
	//TC=Theta(1)
	if (this->size_map == 0) {
		return true;
	}
	return false;
}

SMIterator SortedMap::iterator() const {
	//BC=WC=Theta(1)
	//TC=Theta(1)
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	//BC=WC=Theta(1)
	//TC=Theta(1)
	delete[] this->elements;
}

int SortedMap::updateValues(SortedMap& map){
	//BC=WC=Theta(n)
	//TC=Theta(n);
	int count = 0;
	int k = 0, i = 0;
	while(k<map.size_map && i<this->size_map) {
		if (!this->relation(map.elements[k].first, this->elements[i].first))
			i++;
		if (map.elements[k].first == this->elements[i].first) {
			this->elements[i].second = map.elements[k].second;
			count++;
			i++;
			k++;
		}
	}
	return count;
}

