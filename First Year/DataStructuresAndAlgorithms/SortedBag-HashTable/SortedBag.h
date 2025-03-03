#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;
	friend class Node;

private:
	Node** B;
	int m;
	int bag_size;
	Relation relation;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appear is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	int hash(TComp e, int m)const;
	void resize();

	void addOccurrences(int nr, TComp elem);

	//destructor
	~SortedBag();
};

class Node{
private:
	Node* N;
	TComp I;

public:
	Node() { this->I = NULL_TCOMP; this->N = nullptr; }
	Node(TComp i, Node* n) : I{i},N { n }{ }

	Node* next() { return this->N; }
	TComp info() { return this->I; }

	void SetNext(Node* next) { this->N = next; }
	void SetInfo(TComp info) { this->I = info; }
};