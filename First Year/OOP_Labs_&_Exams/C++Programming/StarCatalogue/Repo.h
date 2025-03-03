#pragma once
#include "Star.h"
#include "Astronomer.h"
#include <vector>
#include <string>

class Repo {
private:
	std::vector<Star> stars;
	std::vector<Astronomer> astronomers;
	std::string stars_file;
	std::string astronomers_file;

public:
	Repo(std::string stars_file, std::string astronomers_file) : stars_file(stars_file), astronomers_file(astronomers_file) {
		this->LoadStars();
		this->LoadAstronomers();
	}

	std::vector<Star>& GetStars() { return stars; }
	std::vector<Astronomer> GetAstronomers() { return astronomers; }

	void LoadStars();
	void LoadAstronomers();
	void SaveStars();

	void AddStar(Star star);
};
