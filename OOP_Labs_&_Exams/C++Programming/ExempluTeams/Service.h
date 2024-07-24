#pragma once
#include <vector>
#include <string>
#include "Repo.h"
#include "Issue.h"
#include "User.h"
#include "Subject.h"

class Service: public Subject {
private:
	Repo& repo;

public:
	Service(Repo& repo): repo(repo){}
	std::vector<Issue> GetIssuesSorted();
	void AddIssue(std::string description, std::string status, std::string reporter, std::string solver);
	void RemoveIssue(Issue issue);
	void ResolveIssue(Issue issue, std::string solver);
};
