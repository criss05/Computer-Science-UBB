#include "Service.h"
#include <algorithm>

using namespace std;


std::vector<Issue> Service::GetIssuesSorted(){
    vector<Issue> issues = repo.GetIssues();
    sort(issues.begin(), issues.end(), [](Issue i1, Issue i2) {
        return i1.GetStatus() < i2.GetStatus() || (i1.GetStatus() == i2.GetStatus() && i1.GetDescription() < i2.GetDescription()); });
    return issues;
}

void Service::AddIssue(std::string description, std::string status, std::string reporter, std::string solver){
    if (description.empty())
        throw exception("Write description first!");
    this->repo.AddIssue(Issue(description, status, reporter, solver));
}

void Service::RemoveIssue(Issue issue){
    this->repo.RemoveIssue(issue);
}

void Service::ResolveIssue(Issue issue, std::string solver){
    this->repo.ResolveIssue(issue, solver);
}
