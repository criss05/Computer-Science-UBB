#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int currentElement;
	int currentFrequency;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

