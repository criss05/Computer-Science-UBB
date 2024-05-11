#pragma once
#include "Service.h"


class UI {
private:
	Portofolio service;

public:
	UI(Portofolio service):service{ service } {}

	void add();
	void showAll();
	void ShowProfitable();
	void saveToFile();

	void printMenu();
	void start();
	void startInput();
};
