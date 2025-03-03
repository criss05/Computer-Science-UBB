#pragma once
#include "Repo.h"


class Service {
private: 
	Repo& repo;

public:
	Service(Repo& repo) : repo(repo) {}

	std::vector<Star>& GetStars() { return repo.GetStars(); }
	std::vector<Star> GetStarsFromConstellation(std::string constellation);
	void AddStar(std::string name, std::string constellation, int RA, int Dec, int diameter);
	std::vector<Star> GetStarsByName(std::string name);
};