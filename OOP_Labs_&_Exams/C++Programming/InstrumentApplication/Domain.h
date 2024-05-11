#pragma once
#include <string>

class Instrument {
protected:
	std::string name;
	double buyPrice;
	double sellPrice;

public:
	Instrument(std::string name, double buyPrice, double sellPrice) : name(name), buyPrice(buyPrice), sellPrice(sellPrice) {}

	virtual double computeProfit() { return sellPrice - buyPrice; }
	virtual std::string toString(){return "Name: " + name + " , Buy Price: " + std::to_string(buyPrice) + " , Sell Price: " + std::to_string(sellPrice); }
};

class Stock : public Instrument {
private:
	double shares;
public:
	Stock(std::string name, double BuyPrice, double SellPrice, double shares) : Instrument(name, BuyPrice, SellPrice), shares(shares) {}

	double computeProfit()override { return Instrument::computeProfit() * shares; }
	std::string toString()override { return Instrument::toString() + " , Type: Stock , Shares: " + std::to_string(shares); }
};

class Option : public Instrument {
private:
	double strikePrice;
	std::string optionType;

public:
	Option(std::string name, double BuyPrice, double SellPrice, double strikePrice, std::string optionType) : Instrument(name, BuyPrice, SellPrice), strikePrice(strikePrice), optionType(optionType) {}

	double computeProfit() override{
		if(optionType == "Call") {
			return sellPrice - strikePrice;
		}
		else {
			return strikePrice - buyPrice;

		}
	}
	std::string toString() override { return Instrument::toString() + " , Type: Option , Strike Price : " + std::to_string(strikePrice) + ", Option Type : " + optionType; }
	

};