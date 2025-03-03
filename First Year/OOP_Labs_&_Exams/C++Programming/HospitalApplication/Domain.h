#pragma once
#include <vector>
#include <string>

using namespace std;

class Patient {
private:
	string name;
	int age;
	bool infected;
	int room;
public:
	Patient(string name, int age, bool infected, int room);

	string GetName();
	int GetAge();
	bool GetInfected();
	int GetRoom();

	void SetInfected(bool new_status);
};