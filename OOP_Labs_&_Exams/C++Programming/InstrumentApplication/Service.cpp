#include "Service.h"
#include <fstream>
#include <algorithm>

using namespace std;

void Portofolio::addInstrument(Instrument* i){
	this->instruments.push_back(i);
}

std::vector<Instrument*> Portofolio::getAllInstruments(){
	return this->instruments;
}

std::vector<Instrument*> Portofolio::getProfitableInstruments(){
	vector <Instrument*> copy;
	for (auto i : this->instruments)
		if (i->computeProfit() > 0)
			copy.push_back(i);
	return copy;
}


bool sortIncreasing(Instrument* a, Instrument* b) {
	return a->computeProfit() < b->computeProfit();
}


void Portofolio::writeToFIle(std::string filename, double maxProfit){
	ofstream f(filename);
	if (f.is_open()) {
		vector<Instrument*> copy;
		for (auto i : this->instruments)
			if (i->computeProfit() < maxProfit)
				copy.push_back(i);
		sort(copy.begin(), copy.end(), sortIncreasing);
		for (auto i : copy)
			f << i->toString() <<" Profit: "<<i->computeProfit()<< endl;
	}
}
