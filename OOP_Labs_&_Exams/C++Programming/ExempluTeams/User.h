#pragma once
#include <string>

class User {
private:
	std::string name;
	std::string type;

public:
	User(std::string name, std::string type) : type(type), name(name) {}

	std::string GetName() { return this->name; }
	std::string GetType() { return this->type; }
};
