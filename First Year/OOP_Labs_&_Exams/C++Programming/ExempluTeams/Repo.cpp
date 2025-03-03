#include "Repo.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <exception>

using namespace std;

void Repo::ReadUsers(){
	ifstream file(this->user_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, type;
		getline(stream, name, ';');
		getline(stream, type, ';');
		this->users.push_back(User(name, type));
	}
	file.close();
}

void Repo::ReadIssues(){
	ifstream file(this->issue_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string description, status, reporter, solver;
		getline(stream, description, ';');
		getline(stream, status, ';');
		getline(stream, reporter, ';');
		getline(stream, solver, ';');
		this->issues.push_back(Issue(description, status, reporter, solver));
	}
	file.close();
}

void Repo::WriteIssues(){
	ofstream file(issue_file);

	for (auto i : this->issues) {
		file << i.GetDescription() << ";" << i.GetStatus() << ";" << i.GetReporter() << ";" << i.GetSolver() << "\n";
	}
	file.close();
}

void Repo::AddIssue(Issue issue){
	auto it = find(this->issues.begin(), this->issues.end(), issue);
	if (it != this->issues.end())
		throw exception("Issue already exists!");
	this->issues.push_back(issue);
	this->WriteIssues();
}

void Repo::RemoveIssue(Issue issue){
	auto it = find(this->issues.begin(), this->issues.end(), issue);
	if ((*it).GetStatus() == "open")
		throw exception("Issue cannot be removed! Close it first.");
	this->issues.erase(it);
	this->WriteIssues();
}

void Repo::ResolveIssue(Issue issue, std::string solver){
	auto it = find(this->issues.begin(), this->issues.end(), issue);
	if ((*it).GetStatus() == "close")
		throw exception("Issue is already solved!");
	(*it).SetSolver(solver);
	(*it).SetStatus("close");
	this->WriteIssues();
}
