#include "Repo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

std::vector<Idea>& Repo::GetIdeas()
{
	sort(ideas.begin(), ideas.end(), [](Idea a, Idea b) { return a.GetAct() < b.GetAct(); });
	return ideas;
}

void Repo::AddIdea(Idea idea){
	for(auto i: ideas)
		if(i.GetDescription() == idea.GetDescription())
			throw exception("Idea already exists");
	ideas.push_back(idea);
}

void Repo::LoadIdeas(){
	ifstream file(ideas_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string description, status, creator, act;
		getline(stream, description, ',');
		getline(stream, status, ',');
		getline(stream, creator, ',');
		getline(stream, act, ',');
		this->ideas.push_back(Idea(description, status, creator, stoi(act)));
	}
	file.close();
}

void Repo::LoadWriters(){
	ifstream file(writers_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, expertise;
		getline(stream, name, ',');
		getline(stream, expertise, ',');
		this->writers.push_back(Writer(name, expertise));
	}
	file.close();
}

void Repo::SaveIdeas(){
	ofstream file("ideas_save.txt");
	file << "Act 1\n";
	for (auto idea : ideas) {
		if(idea.GetStatus() == "accepted" && idea.GetAct() == 1)
			file << idea.GetDescription() << "(" << idea.GetCreator() << ")\n";
	}
	file << "Act 2\n";
	for (auto idea : ideas) {
		if (idea.GetStatus() == "accepted" && idea.GetAct() == 2)
			file << idea.GetDescription() << "(" << idea.GetCreator() << ")\n";
	}
	file << "Act 3\n";
	for (auto idea : ideas) {
		if (idea.GetStatus() == "accepted" && idea.GetAct() == 3)
			file << idea.GetDescription() << "(" << idea.GetCreator() << ")\n";
	}
}
