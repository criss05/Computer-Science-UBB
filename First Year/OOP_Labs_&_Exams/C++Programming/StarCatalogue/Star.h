#pragma once
#include <string>


class Star {
private:
	std::string name;
	std::string constellation;
	int RA;
	int Dec;
	int diameter;

public:
	Star(std::string name="", std::string cst="", int RA=0, int Dec=0, int diameter=0) : name(name), constellation(cst), RA(RA), Dec(Dec), diameter(diameter) {}

	std::string GetName() { return name; }
	std::string GetConstellation() { return constellation; }
	int GetRA() { return RA; }
	int GetDec() { return Dec; }
	int GetDiameter() { return diameter; }
};
