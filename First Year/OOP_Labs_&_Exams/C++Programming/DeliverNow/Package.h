#pragma once
#include <string>


class Package {
private:
	std::string recipient;
	std::string street;
	int number;
	int x;
	int y;
	bool status;

public:
	Package(std::string recipient, std::string street, int number, int x, int y, bool status): recipient(recipient), street(street), number(number), x(x), y(y), status(status) {}

	std::string GetRecipient() { return recipient; }
	std::string GetStreet() { return street; }
	int GetNumber() { return number; }
	int GetX() { return x; }
	int GetY() { return y; }
	bool GetStatus() { return status; }

	void SetStatus(bool isDelivered) { this->status = isDelivered; }
};
