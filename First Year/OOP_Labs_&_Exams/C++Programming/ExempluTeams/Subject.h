#pragma once

#include "Observer.h"
#include <vector>

class Subject {
private:
	std::vector<Observer*> observers;

public:
	void RegisterObserver(Observer* observer);
	void notify();
};