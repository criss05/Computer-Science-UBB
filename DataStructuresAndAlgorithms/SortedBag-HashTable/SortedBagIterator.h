#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;
	friend class Node;
 
private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int current_minim_position = -1;
	Node** array;
	int array_size;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	int getSize() { return array_size; }
};

