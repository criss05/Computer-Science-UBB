#pragma once
#include <string>


class Astronomer {
private:
	std::string name;
	std::string constellation;

public:
	Astronomer(std::string name, std::string cst) : name(name), constellation(cst) {}

	std::string GetName() { return name; }
	std::string GetConstellation() { return constellation; }
};