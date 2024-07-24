#include "Repo.h"
#include <sstream>
#include <fstream>

using namespace std;

void Repo::LoadCouriers(){
	ifstream file(couriers_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string name, streets, x, y, radius;
		getline(stream, name, ';');
		getline(stream, streets, ';');
		getline(stream, x, ';');
		getline(stream, y, ';');
		getline(stream, radius, ';');
		stringstream str(streets);
		string street;
		vector<string> streets_vector;
		while (getline(str, street,'|'))
			streets_vector.push_back(street);
		couriers.push_back(Courier(name, streets_vector, stoi(x), stoi(y), stoi(radius)));
	}
	file.close();
}

void Repo::LoadPackages(){
	ifstream file(packages_file);
	string line;
	while (getline(file, line)) {
		stringstream stream(line);
		string recipient, street, number, x, y,status;
		getline(stream, recipient, ';');
		getline(stream, street, ';');
		getline(stream, number, ';');
		getline(stream, x, ';');
		getline(stream, y, ';');
		getline(stream, status, ';');
		bool s = true;
		if (status == "False")
			s = false;
		packages.push_back(Package(recipient, street, stoi(number), stoi(x), stoi(y), s));
	}
	file.close();
}

void Repo::SavePackages() {
	ofstream file(packages_file);
	for (auto p : packages)
	{
		string std_status;
		if (p.GetStatus())
			std_status = "True";
		else
			std_status = "False";
		file << p.GetRecipient() << ";" << p.GetStreet() << ";" << p.GetNumber() << ";" << p.GetX() << ";" << p.GetY() << ";" << p.GetStatus() << "\n";
	}
}
