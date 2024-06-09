#include "Matrix.h"
#include <exception>
#include <iostream>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	//BC=WC=TC=Theta(1)
	root = nullptr;
	nr_lines = nrLines;
	nr_columns = nrCols;
}


int Matrix::nrLines() const {
	//BC=WC=TC=Theta(1)
	return nr_lines;
}


int Matrix::nrColumns() const {
	//BC=WC=TC=Theta(1)
	return nr_columns;
}


TElem Matrix::element(int i, int j) const {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (i<0 || i>nr_lines)
		throw exception();
	if (j<0 || j>nr_columns)
		throw exception();

	Node* node = root;
	while (node != nullptr) {
		if (node->i == i && node->j == j)
			return node->value;
		if (i < node->i || (i == node->i && j < node->j))
			node = node->left;
		else if (i > node->i || (i == node->i && j > node->j))
			node = node->right;
	}
	if (node == nullptr)
		return NULL_TELEM;
	else
		return node->value;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (i<0 || i>nr_lines)
		throw exception();
	if (j<0 || j>nr_columns)
		throw exception();

	Node* current = root;
	Node* prev = nullptr;
	while (current != nullptr && (current->i != i || current->j != j)) {
		prev = current;
		if (i < current->i || (i == current->i && j < current->j))
			current = current->left;
		else if (i > current->i || (i == current->i && j > current->j))
			current = current->right;
	}
	if (current == nullptr) {
		if (e == NULL_TELEM)
			return NULL_TELEM;
		if (e != NULL_TELEM) {
			if (root == nullptr) {
				Node* node = new Node;
				node->i = i;
				node->j = j;
				node->value = e;
				node->left = nullptr;
				node->right = nullptr;
				root = node;
				size++;
				return NULL_TELEM;
			}
			else {
				Node* node = new Node;
				node->i = i;
				node->j = j;
				node->value = e;
				node->left = nullptr;
				node->right = nullptr;
				if (prev->i < node->i || (prev->i == node->i && prev->j < node->j))
					prev->right = node;
				else if (prev->i > node->i || (prev->i == node->i && prev->j > node->j))
					prev->left = node;
				size++;
				return NULL_TELEM;
			}
		}
	}
	else if (i==current->i && j==current->j){
		if (e == NULL_TELEM) {
			if (current != root) {
				TElem old_value = current->value;
				//The node has no children
				if (current->left == nullptr && current->right == nullptr) {
					if (prev->right == current)
						prev->right = nullptr;
					else if (prev->left == current)
						prev->left = nullptr;
					delete current;
					return old_value;
				}
				//The node has one children on the left
				if (current->left != nullptr && current->right == nullptr) {
					if (prev->right == current)
						prev->right = current->left;
					else if (prev->left == current)
						prev->left = current->left;
					delete current;
					return old_value;
				}
				//The node has one children on the right
				if (current->left == nullptr && current->right != nullptr) {
					if (prev->right == current)
						prev->right = current->right;
					else if (prev->left == current)
						prev->left = current->right;
					delete current;
					return old_value;
				}
				//The node has two children
				if (current->left != nullptr && current->right != nullptr) {
					Node* new_current = current->right;
					Node* new_prev = current;
					Node* parent = nullptr;
					while (new_current != nullptr) {
						parent = new_prev;
						new_prev = new_current;
						new_current = new_current->left;
					}
					current->i = new_prev->i;
					current->j = new_prev->j;
					current->value = new_prev->value;
					if (parent->left == new_prev) {
						parent->left = new_prev->right;
					}
					else {
						parent->right = new_prev->right;
					}
					delete new_prev;
					return old_value;
				}
			}
			else {
				TElem old_value = root->value;
				//The root has no children
				if (current->left == nullptr && current->right == nullptr) {
					root = nullptr;
					delete current;
					return old_value;
				}
				//The node has one children on the left
				if (current->left != nullptr && current->right == nullptr) {
					root = current->left;
					delete current;
					return old_value;
				}
				//The node has one children on the right
				if (current->left == nullptr && current->right != nullptr) {
					root = current->right;
					delete current;
					return old_value;
				}
				//The node has two children
				if (current->left != nullptr && current->right != nullptr) {
					Node* new_current = current->right;
					Node* new_prev = current;
					Node* parent = nullptr;
					while (new_current != nullptr) {
						parent = new_prev;
						new_prev = new_current;
						new_current = new_current->left;
					}
					current->i = new_prev->i;
					current->j = new_prev->j;
					current->value = new_prev->value;
					if (parent->left == new_prev) {
						parent->left = new_prev->right;
					}
					else {
						parent->right = new_prev->right;
					}
					delete new_prev;
					return old_value;
				}
			}
		}
		if (e != NULL_TELEM) {
			TElem old_value = current->value;
			current->value = e;
			return old_value;
		}
	}
	return NULL_TELEM;
}

pair<int, int> Matrix::positionOf(TElem elem) const{
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	Node** stack = new Node * [size];
	int index = -1;
	Node* current = root;
	while (current != nullptr) {
		index++;
		stack[index] = current;
		current = current->left;
	}
	while(index!= -1){
		current = stack[index];
		index--;
		if (current->value == elem)
			return make_pair(current->i, current->j);

		current = current->right;
		while (current != nullptr) {
			index++;
			stack[index] = current;
			current = current->left;
		}
	}
	delete[] stack;
	return make_pair(-1, -1);
}