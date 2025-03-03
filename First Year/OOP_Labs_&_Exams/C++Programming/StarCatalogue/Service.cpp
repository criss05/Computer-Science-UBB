#include "Service.h"
#include <iostream>
#include <algorithm>

using namespace std;

std::vector<Star> Service::GetStarsFromConstellation(string constellation)
{
    vector<Star>& stars = repo.GetStars();
    vector<Star> copy;
    copy_if(stars.begin(), stars.end(), back_inserter(copy), [constellation](Star s) {return s.GetConstellation() == constellation; });
    return copy;
}

void Service::AddStar(std::string name, std::string constellation, int RA, int Dec, int diameter){
    if (diameter <= 0)
        throw exception("Diameter less then 0!");
    if (name.empty())
        throw exception("Name is empty!");
    repo.AddStar(Star(name, constellation, RA, Dec, diameter));
}

std::vector<Star> Service::GetStarsByName(std::string name)
{
    vector<Star>& stars = repo.GetStars();
    vector<Star> copy;
    for (auto s : stars)
        if (s.GetName().find(name) != std::string::npos)
            copy.push_back(s);
    return copy;
}
