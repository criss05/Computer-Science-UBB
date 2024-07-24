#include "Subject.h"

void Subject::RegisterObserver(Observer* observer){
	observers.push_back(observer);
}

void Subject::notify(){
	for (auto o : observers)
		o->update();
}
