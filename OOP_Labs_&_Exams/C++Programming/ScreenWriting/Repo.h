#pragma once
#include <vector>
#include <string>
#include "Idea.h"
#include "Writer.h"

class Repo {
private:
	std::vector<Idea> ideas;
	std::vector<Writer> writers;
	std::string ideas_file;
	std::string writers_file;

public:
	Repo(std::string ideas_file, std::string writers_file) : ideas_file(ideas_file), writers_file(writers_file) {
		LoadIdeas();
		LoadWriters();
	}

	std::vector<Idea>& GetIdeas();
	std::vector<Writer>& GetWriters() { return writers; }

	void AddIdea(Idea idea);
	
	void LoadIdeas();
	void LoadWriters();
	void SaveIdeas();
};
