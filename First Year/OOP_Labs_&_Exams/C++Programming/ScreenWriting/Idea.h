#pragma once
#include <string>


class Idea {
private:
	std::string description;
	std::string status;
	std::string creator;
	int act;

public:
	Idea(std::string descr, std::string status, std::string creator, int act): description(descr), status(status), creator(creator), act(act) {}

	std::string GetDescription() const { return description; }
	std::string GetStatus() const { return status; }
	std::string GetCreator() const { return creator; }
	int GetAct() const { return act; }

	void SetStatus(std::string newStatus) { status = newStatus; }
};
