#pragma once
#include "Repo.h"
#include <vector>
#include <string>
#include "Subject.h"


class Service : public Subject{
private:
	Repo& repo;

public:
	Service(Repo& r) : repo(r) {}

	std::vector<Courier> GetCouriers() { return repo.GetCouriers(); }
	std::vector<Package> GetUndeliveredPackages();

	std::vector<Package>& GetAllPackages() { return repo.GetPackages(); }
	std::vector<Package> GetPackagesFromStreet(std::string street);
	void ModifyPackageStatus(std::string recipient);

	void AddPackages(std::string recipient, std::string street, int number, int x, int y, bool status);
};