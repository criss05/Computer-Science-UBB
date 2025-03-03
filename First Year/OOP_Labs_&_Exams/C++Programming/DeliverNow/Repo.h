#pragma once
#include "Courier.h"
#include "Package.h"
#include <string>
#include <vector>

class Repo {
private:
	std::vector<Courier> couriers;
	std::vector<Package> packages;
	std::string couriers_file;
	std::string packages_file;

public:
	Repo(std::string couriers_file, std::string packages_file) : couriers_file(couriers_file), packages_file(packages_file) { LoadCouriers(); LoadPackages(); }

	void LoadCouriers();
	void LoadPackages();
	void SavePackages();

	std::vector<Courier> GetCouriers() { return couriers; }
	std::vector<Package>& GetPackages() { return packages; }

	void AddPackages(Package p) { packages.push_back(p); }
};
