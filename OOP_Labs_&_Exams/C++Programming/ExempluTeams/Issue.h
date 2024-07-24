#pragma once
#include <string>

class Issue {
private:
	std::string description;
	std::string status;
	std::string reporter;
	std::string solver;

public:
	Issue(std::string descr, std::string status, std::string rep, std::string sol) : description(descr), status(status), reporter(rep), solver(sol) {}

	std::string GetDescription() { return this->description; }
	std::string GetStatus() { return this->status; }
	std::string GetReporter() { return this->reporter; }
	std::string GetSolver() { return this->solver; }

	void SetStatus(std::string status) { this->status = status; }
	void SetSolver(std::string solver) { this->solver = solver; }

	bool operator==(Issue issue) { return issue.description == this->description; }
};
