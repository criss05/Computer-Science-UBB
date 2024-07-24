#pragma once
#include "Observer.h"
#include <vector>


class Subject {
private:
	std::vector<Observer*> observers;

public:
	void notify() {
		for (auto o : observers)
			o->Update();
	}
	void RegisterObserver(Observer* o) {
				observers.push_back(o);
	}
};