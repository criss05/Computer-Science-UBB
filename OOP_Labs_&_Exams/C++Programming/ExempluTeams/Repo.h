#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Issue.h"



class Repo {
private:
	std::vector<User> users;
	std::vector<Issue> issues;
	std::string user_file;
	std::string issue_file;


public:
	Repo(std::string user_file, std::string issue_file) : user_file(user_file), issue_file(issue_file) { this->ReadUsers(); this->ReadIssues(); }

	std::vector<User> GetUser() { return this->users; }
	std::vector<Issue>& GetIssues() { return this->issues; }

	void ReadUsers();
	void ReadIssues();

	void WriteIssues();

	void AddIssue(Issue issue);
	void RemoveIssue(Issue issue);
	void ResolveIssue(Issue issue, std::string solver);
};
