#pragma once
#include <string>


class Writer {
private:
	std::string name;
	std::string expertise;

public:
	Writer(std::string name, std::string exp) : name(name), expertise(exp) {}

	std::string GetName() { return name; }
	std::string GetExpertise() { return expertise; }
};
