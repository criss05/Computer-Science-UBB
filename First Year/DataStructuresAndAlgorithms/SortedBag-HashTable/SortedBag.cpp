#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cmath>
#include <exception>

SortedBag::SortedBag(Relation r) {
	//WC=BC=TC=Theta(m)
	//m-capacity
	this->relation = r;
	this->m = 10;
	this->B = new Node * [this->m];
	this->bag_size = 0;
	for (int i = 0; i < m; i++)
		B[i] = nullptr;
}

void SortedBag::add(TComp e) {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	//n - number of elements in the corresponding list
	int pos = hash(e, this->m);
	Node* current = this->B[pos];
	Node* prev = nullptr;
	while (current != nullptr && relation(current->info(),e))
	{
		prev = current;
		current = current->next();
	}
	if (current == nullptr && prev == nullptr) {
		Node* new_node = new Node(e, nullptr);
		this->B[pos] = new_node;
	}
	if (current == nullptr && prev != nullptr) {
		Node* new_node = new Node(e, nullptr);
		prev->SetNext(new_node);
	}
	if (current != nullptr && prev == nullptr) {
		Node* new_node = new Node(e, B[pos]);
		this->B[pos] = new_node;
	}
	if (current != nullptr && prev != nullptr) {
		Node* new_node = new Node(e, current);
		prev->SetNext(new_node);
	}
	this->bag_size++;
	if ((double)bag_size / m >= 0.7)
		resize();
}


bool SortedBag::remove(TComp e) {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	//n - number of elements in the corresponding list
	int pos = hash(e, this->m);
	Node* current = B[pos];
	Node* prev = nullptr;
	while(current!=nullptr){
		if (current->info() == e) {
			Node* node = current;
			if (prev == nullptr)
				B[pos] = current->next();
			else
				prev->SetNext(current->next());
			delete node;
			this->bag_size--;
			return true;
		}
		if (!relation(current->info(), e)) {
			return false;
		}
		prev = current;
		current = current->next();
	}
	return false;
}


bool SortedBag::search(TComp elem) const {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	//n - number of elements in the corresponding list
	int pos = hash(elem, this->m);

	Node* current = B[pos];
	while(current != nullptr){
		if (current->info() == elem)
			return true;
		if (!relation(current->info(), elem))
			return false;
		current = current->next();
	}
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	//n - number of elements in the corresponding list
	int pos = hash(elem, this->m);

	Node* current = B[pos];
	int nr = 0;
	while (current != nullptr && this->relation(current->info(),elem)) {
		if(current->info() == elem)
			nr++;

		current = current->next();
	}
	return nr;
}



int SortedBag::size() const {
	//BC=WC=TC=Theta(1)
	return this->bag_size;
}


bool SortedBag::isEmpty() const {
	//BC=WC=TC=Theta(1)
	return this->bag_size == 0;
}

int SortedBag::hash(TComp e, int m) const{
	//BC=WC=TC=Theta(1)
	return e%m >=0 ? e%m : e%m + m;
}

void SortedBag::resize(){
	//BC=Theta(m) - one element in each list
	//WC=Theta((n^2)*m) - n^2 - all elements on the same list
	//TC=O((n^2)*m)
	Node** new_B = new Node * [m*2];
	for (int i = 0; i < m*2; i++)
		new_B[i] = nullptr;

	for (int i = 0; i < m; i++) {
		Node* current = B[i];
		Node* prev = nullptr;
		while (current != nullptr) {
			int new_pos = hash(current->info(), m*2);
			Node* new_current = new_B[new_pos];
			Node* new_prev = nullptr;
			while (new_current != nullptr && relation(new_current->info(), current->info()))
			{
				new_prev = new_current;
				new_current = new_current->next();
			}
			if (new_current == nullptr && new_prev == nullptr) {
				Node* new_node = new Node(current->info(), nullptr);
				new_B[new_pos] = new_node;
			}
			if (new_current == nullptr && new_prev != nullptr) {
				Node* new_node = new Node(current->info(), nullptr);
				new_prev->SetNext(new_node);
			}
			if (new_current != nullptr && new_prev == nullptr) {
				Node* new_node = new Node(current->info(), new_B[new_pos]);
				new_B[new_pos] = new_node;
			}
			if (new_current != nullptr && new_prev != nullptr) {
				Node* new_node = new Node(current->info(), new_current);
				new_prev->SetNext(new_node);
			}
			prev = current;
			current = current->next();
			delete prev;
		}
	}
	delete[] B;
	B = new_B;
	m = m * 2;
}

void SortedBag::addOccurrences(int nr, TComp elem){
	//BC=Theta(1)
	//WC=Theta(n)
	//TC=O(n)
	if (nr < 0)
		throw std::exception();
	Node* first = new Node(elem, nullptr);
	Node* last = first;
	nr--;
	while (nr > 0) {
		Node* new_node = new Node(elem, first);
		first = new_node;
		nr--;
	}
	int pos = hash(elem, this->m);
	Node* current = this->B[pos];
	Node* prev = nullptr;
	while (current != nullptr && relation(current->info(), elem))
	{
		prev = current;
		current = current->next();
	}
	if (current == nullptr && prev == nullptr) {
		this->B[pos] = first;
	}
	if (current == nullptr && prev != nullptr) {
		prev->SetNext(first);
		last->SetNext(current);
	}
	if (current != nullptr && prev == nullptr) {
		last->SetNext(this->B[pos]);
		this->B[pos] = first;
	}
	if (current != nullptr && prev != nullptr) {
		prev->SetNext(first);
		last->SetNext(current);
	}
	this->bag_size++;
	if ((double)bag_size / m >= 0.7)
		resize();

}

SortedBagIterator SortedBag::iterator() const {
	//BC=Theta(m+n)
	//WC=Theta(m*n)
	//TC=O(m*n)
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//BC=Theta(m) - one element in each list
	//WC=Theta(m+n) - n-number of elements in the bag; all elements in the same list
	//TC=O()
	for (int i = 0; i < m; i++) {
		Node* current = B[i];
		Node* prev = nullptr;
		while (current != nullptr) {
			prev = current;
			current = current->next();
			delete prev;
		}
	}
	delete[] B;
}
