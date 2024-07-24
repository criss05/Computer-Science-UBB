#pragma once
#include <string>
#include <vector>


class Courier {
private:
	std::string name;
	std::vector<std::string> streets;
	int x;
	int y;
	int radius;

public:
	Courier(std::string name, std::vector<std::string> streets, int x, int y, int radius): name(name), streets(streets), x(x), y(y), radius(radius) {}

	std::string GetName() { return name; }
	std::vector<std::string> GetStreets() { return streets; }
	int GetX() { return x; }
	int GetY() { return y; }
	int GetRadius() { return radius; }
};
