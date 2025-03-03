#pragma once


//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
#include <utility>

class Matrix {
	friend class Node;
private:
	Node* head;
	int nrL;
	int nrC;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	~Matrix();

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

	//sets all the values from the main diagonal to the value elem.
	//throws an exception if it is not a square matrix.
	void setMainDiagonal(TElem elem);
};

class Node {
private:
	int L;
	int C;
	TElem V;
	Node* N;
public:
	Node(int line, int column, TElem value, Node* next) : L(line), C(column), V(value), N(next) {};
	Node* next() { return this->N; }
	int line() { return this->L; }
	int column() { return this->C; }
	TElem value() { return this->V; }

	void SetValue(TElem new_value) { this->V = new_value; }
	void SetNext(Node* next) { this->N = next; }
};
