#pragma once
#include <vector>
#include <string>
#include "Domain.h"

class Portofolio {
private:
	std::vector<Instrument*> instruments;

public:
	void addInstrument(Instrument* i);
	std::vector<Instrument*> getAllInstruments();
	std::vector<Instrument*> getProfitableInstruments();
	void writeToFIle(std::string filename, double maxProfit);
};