#include "Repo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

void Repo::LoadStars(){
	ifstream file(this->stars_file);
	
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, constellation, RA, Dec, diameter;

		getline(stream, name, ',');
		getline(stream, constellation, ',');
		getline(stream, RA, ',');
		getline(stream, Dec, ',');
		getline(stream, diameter, ',');

		this->stars.push_back(Star(name, constellation, stoi(RA), stoi(Dec), stoi(diameter)));
	}
	file.close();
}

void Repo::LoadAstronomers(){
	ifstream file(this->astronomers_file);

	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, constellation;

		getline(stream, name, ',');
		getline(stream, constellation, ',');
		this->astronomers.push_back(Astronomer(name, constellation));
	}
	file.close();
}

void Repo::SaveStars(){
	ofstream file(stars_file);

	sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2) {return s1.GetConstellation() < s2.GetConstellation(); });
	for(auto s: this->stars)
		file << s.GetName() << "," << s.GetConstellation() << "," << s.GetRA() << "," << s.GetDec() << "," << s.GetDiameter() << "\n";
}

void Repo::AddStar(Star star){
	for(auto s : stars){
		if (s.GetName() == star.GetName())
			throw exception("The star already exists!");
	}
	this->stars.push_back(star);
	SaveStars();
}
