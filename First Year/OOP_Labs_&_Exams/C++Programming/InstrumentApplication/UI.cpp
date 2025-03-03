#include "UI.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void UI::add(){
	string name, buyPrice, selPrice, type;

	cout<<"Enter the name of the product: ";
	getline(cin, name);

	cout<<"Enter the buying price of the product: ";
	getline(cin, buyPrice);
	
	cout<<"Enter the selling price of the product: ";
	getline(cin, selPrice);

	cout<<"Enter the type of the product:  (1. Stock/2. Option)";
	getline(cin, type);

	if (type == "1") {
		string shares;
		cout << "Give the shares: ";
		getline(cin, shares);
		Stock* a = new Stock(name, stod(buyPrice), stod(selPrice), stod(shares));
		this->service.addInstrument(a);
	}
	else {
		string stikePrice, optionType;
		cout<<"Enter the strike price of the option: ";
		getline(cin, stikePrice);

		cout<<"Enter the type of the option:  (1. Call/2. Put)";
		getline(cin, optionType);
		if (optionType == "1")
			optionType = "Call";
		else
			optionType = "Put";
		Option* o = new Option(name, stod(buyPrice), stod(selPrice), stod(stikePrice), optionType);
		this->service.addInstrument(o);
	}
}

void UI::showAll(){
	vector<Instrument*> instruments = this->service.getAllInstruments();
	for (auto i : instruments) {
		cout<<i->toString()<<endl;
	}
}

void UI::ShowProfitable(){
	vector<Instrument*> instruments = this->service.getProfitableInstruments();
	for (auto i : instruments)
		cout << i->toString() << " Profit: " << i->computeProfit() << endl;
}

void UI::saveToFile(){
	string profit;
	cout << "Give the profit: ";
	getline(cin, profit);
	this->service.writeToFIle("file.txt", stoi(profit));
}

void UI::printMenu(){
	cout<<"1. Add a new instrument"<<endl;
	cout<<"2. Show all instruments"<<endl;
	cout<<"3. Show all profitable instruments"<<endl;
	cout<<"4. Save to file"<<endl;
	cout<<"5. Exit"<<endl;
}

void UI::start(){
	this->startInput();
	while (1) {
		this->printMenu();
		string option;
		cout << "Choose an option: ";
		getline(cin, option);
		switch (stoi(option)) {
		case 1:
			this->add();
			break;
		case 2:
			this->showAll();
			break;
		case 3:
			this->ShowProfitable();
			break;
		case 4:
			this->saveToFile();
			break;
		case 5:
		{
			cout << "Exiting..." << endl;
			return;
		}
		default:
			cout << "Invalid option" << endl;
			break;
		}
	}
}

void UI::startInput(){
	Stock* s1 = new Stock("AAPL", 150, 150.5, 100);
	Option* o = new Option("KO", 100, 101.5, 105, "Call");
	Stock* s2 = new Stock("BRKR", 7, 6.80, 20);

	this->service.addInstrument(s1);
	this->service.addInstrument(o);
	this->service.addInstrument(s2);
}


int main() {
	Portofolio service;
	UI ui(service);
	ui.start();
	return 0;
}