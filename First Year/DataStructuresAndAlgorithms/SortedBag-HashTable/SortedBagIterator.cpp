#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//BC=WC=TC=Theta(m)
	array = new Node*[bag.m];
	int i = 0;
	int j = 0;
	while(i!=bag.m) {
		if (bag.B[i] == nullptr)
			i++;
		else {
			if (current_minim_position == -1)
				current_minim_position = j;
			else if (bag.relation(bag.B[i]->info(), array[current_minim_position]->info()))
				current_minim_position = j;
			array[j] = bag.B[i];
			i++;
			j++;
		}
	}

	array_size = j;
}


TComp SortedBagIterator::getCurrent() {
	//WC=BC=TC=Theta(1)
	if (current_minim_position >= array_size || current_minim_position == -1)
		throw exception();
	return array[current_minim_position]->info();
}

bool SortedBagIterator::valid() {
	//WC=BC=TC=Theta(1)
	return current_minim_position < array_size && current_minim_position != -1;
}

void SortedBagIterator::next() {
	//BC=Theta(1)
	//WC=Theta(m)
	//TC=O(m)
	if (current_minim_position >= array_size || current_minim_position == -1)
		throw exception();
	Node* next_node = array[current_minim_position]->next();
	TComp old_minim = array[current_minim_position]->info();
	if (next_node != nullptr) {
		array[current_minim_position] = next_node;
	}
	else 
		if(current_minim_position != array_size-1){
			array[current_minim_position] = array[array_size-1];
			array_size--;
		}
		else {
			current_minim_position=0;
			array_size--;
		}
	if (array[current_minim_position]->info() != old_minim) {
		int i = 0;
		while (i != array_size) {
			if (!bag.relation(array[current_minim_position]->info(),array[i]->info()))
				current_minim_position = i;
			i++;
		}
	}
	if (array_size == 0)
		current_minim_position = -1;
}

void SortedBagIterator::first() {
	//BC=WC=TC=Theta(m)
	int i = 0;
	int j = 0;
	while (i != bag.m) {
		if (bag.B[i] == nullptr)
			i++;
		else {
			if (current_minim_position == -1)
				current_minim_position = j;
			else if (bag.relation(bag.B[i]->info(), array[current_minim_position]->info()))
				current_minim_position = j;
			array[j] = bag.B[i];
			i++;
			j++;
		}
	}
	array_size = j;
}