#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	//WC=BC=Theta(1)
	//TC=Theta(1)
	this->head = nullptr;
	this->nrL = nrLines;
	this->nrC = nrCols;
}

Matrix::~Matrix(){
	//BC=WC=Theta(n)
	//TC=Theta(n)
	Node* prev = nullptr;
	Node* current = this->head;
	while (current != nullptr) {
		prev = current;
		current = current->next();
		delete prev;
	}
}


int Matrix::nrLines() const {
	//WC=BC=Theta(1)
	//TC=Theta(1)
	return this->nrL;
}


int Matrix::nrColumns() const {
	//WC=BC=Theta(1)
	//TC=Theta(1)
	return this->nrC;
}


TElem Matrix::element(int i, int j) const {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (i<0 or i>this->nrL)
		throw exception();
	if (j<0 or j>this->nrC)
		throw exception();
	
	Node* current = this->head;
	while (current != nullptr) {
		if (current->line() == i && current->column() == j)
			return current->value();
		current = current->next();
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e){
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (i<0 or i>this->nrL)
		throw exception();
	if (j<0 or j>this->nrC)
		throw exception();
	Node* current = this->head;
	Node* prev = nullptr;

	if (current == nullptr) {
		Node* new_node = new Node{ i,j,e, nullptr };
		this->head = new_node;
		return NULL_TELEM;
	}

	while (current->next() != nullptr && (current->next()->line() < i || (current->next()->line() == i && current->next()->column() <= j)))
	{
		prev = current;
		current = current->next();
	}
	
	if (current->line() == i && current->column() == j) {
		if (current == this->head && e == NULL_TELEM) {
			TElem old = current->value();
			this->head = this->head->next();
			delete current;
			return old;
		}
		if (e != NULL_TELEM) {
			TElem old = current->value();
			current->SetValue(e);
			return old;
		}
		else {
			prev->SetNext(current->next());
			TElem old = current->value();
			delete current;
			return old;
		}
	}
	if (current != nullptr) {
		if (e == NULL_TELEM) {
			return NULL_TELEM;
		}
		if (e != NULL_TELEM) {
			Node* new_node = new Node{ i,j,e,current->next() };
			current->SetNext(new_node);
			return NULL_TELEM;
		}
	}
}

void Matrix::setMainDiagonal(TElem elem){
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (this->nrC != this->nrL)
		throw exception("Not a square matrix");

	Node* current = this->head;
	Node* prev = nullptr;

	if (current == nullptr) {
		Node* new_node = new Node{ 0,0,elem, nullptr };
		this->head = new_node;
	}
	if (current->line() != 0 && current->column() != 0) {
		Node* new_node = new Node{ 0,0, elem, this->head };
		this->head = new_node;
	}

	int i = 0;
	Node* inode = this->head;
	while(i!=this->nrL){
		current = inode;
		while (current->next() != nullptr && (current->next()->line() < i || (current->next()->line() == i && current->next()->column() <= i)))
		{
			prev = current;
			inode = current;
			current = current->next();
		}

		if (current->line() == i && current->column() == i) {
			if (current == this->head && elem == NULL_TELEM) {
				this->head = this->head->next();
				delete current;
			}
			if (elem != NULL_TELEM) {
				current->SetValue(elem);
			}
			else {
				prev->SetNext(current->next());
				delete current;
			}
		}
		if (current != nullptr) {
			if (elem == NULL_TELEM) {
				return;
			}
			if (elem != NULL_TELEM) {
				Node* new_node = new Node{ i,i,elem,current->next() };
				current->SetNext(new_node);
			}
		}
		i++;
	}
}
