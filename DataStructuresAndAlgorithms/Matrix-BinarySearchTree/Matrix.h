#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <utility>
#include <iostream>

class Matrix {

private:
	
	typedef struct Node {
		TElem value;
		int i;
		int j;
		Node* left;
		Node* right;
	};

	Node* root;
	int nr_lines;
	int nr_columns;
	int size;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the position of an element in the matrix(as line and column pair)
	// if elem occurs multiple time returs any position of it
	// if elem is not in the matrix returns (-1,-1)
	std::pair<int, int> positionOf(TElem elem)const;
};