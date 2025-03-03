#include "Service.h"
#include <algorithm>
#include <iostream>
using namespace std;


std::vector<Package> Service::GetUndeliveredPackages()
{
    vector<Package> packages = repo.GetPackages();
    vector<Package> copy;
    copy_if(packages.begin(), packages.end(), back_inserter(copy), [](Package p) {return !p.GetStatus(); });
    return copy;
}

std::vector<Package> Service::GetPackagesFromStreet(string street)
{
    vector<Package> packages = repo.GetPackages();
    vector<Package> copy;
    copy_if(packages.begin(), packages.end(), back_inserter(copy), [street](Package p) {return !p.GetStatus() && p.GetStreet() == street; });
    return copy;
}

void Service::ModifyPackageStatus(std::string recipient){
    for (auto& p : repo.GetPackages()) {
        if (p.GetRecipient() == recipient)
            p.SetStatus(true);
    }
    repo.SavePackages();
}

void Service::AddPackages(std::string recipient, std::string street, int number, int x, int y, bool status){
    repo.AddPackages(Package(recipient, street, number, x, y, status));
    repo.SavePackages();
}
