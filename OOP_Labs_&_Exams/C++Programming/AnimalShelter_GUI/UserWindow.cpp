#include "UserWindow.h"
#include "RepoException.h"
#include <qlabel.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <vector>
#include <qmessagebox.h>

UserWindow::UserWindow(Service& service,  QWidget* parent)
	: QWidget(parent), service{ service }
{
	ui.setupUi(this);
	this->initUserWindow();
	this->PopulateAdoptedList();
	this->ConnectSignals();
}

UserWindow::~UserWindow(){}

void UserWindow::initUserWindow(){
	QVBoxLayout* user_layout = new QVBoxLayout{this};

	QFormLayout* filter_data = new QFormLayout;
	QLabel* breed_filter_label = new QLabel{ "Breed" };
	breed_filter_edit = new QLineEdit;
	filter_data->addRow(breed_filter_label, breed_filter_edit);
	QLabel* age_filter_label = new QLabel{ "Age" };
	age_filter_edit = new QLineEdit;
	filter_data->addRow(age_filter_label, age_filter_edit);
	user_layout->addLayout(filter_data);

	adopted_one_by_one = new QListWidget{};
	user_layout->addWidget(adopted_one_by_one);

	QGridLayout* buttons_adoption_layout = new QGridLayout;
	open_button = new QPushButton{ "Open" };
	adopt_button = new QPushButton{ "Adopt" };
	next_button = new QPushButton{ "Next" };
	buttons_adoption_layout->addWidget(open_button, 0, 0);
	buttons_adoption_layout->addWidget(adopt_button, 0, 1);
	buttons_adoption_layout->addWidget(next_button, 0, 2);
	user_layout->addLayout(buttons_adoption_layout);

	user_layout->addSpacing(10);

	adopted_list = new QListWidget{};
	user_layout->addWidget(adopted_list);

	open_list_button = new QPushButton{ "Open adoption list" };
	user_layout->addWidget(open_list_button);

	go_back_button = new QPushButton{ "Go back" };
	user_layout->addWidget(go_back_button);

	setWindowTitle("User Mode");
	setWindowIcon(QIcon("user.jpg"));
}

void UserWindow::PopulateAdoptedList() {
	this->adopted_list->clear();
	std::vector<Pet> pets = this->service.GetPetsFromAdoptionList();

	for (auto pet : pets)
		this->adopted_list->addItem(QString::fromStdString(pet.GetBreed() + " | " + pet.GetName() + " | " + std::to_string(pet.GetAge()) + " | " + pet.GetPhotograph()));
}

void UserWindow::PopulateAdoptedFilteredList(){
	if (adopted_filtered.size() > 0) {
		this->adopted_one_by_one->clear();
		Pet pet = adopted_filtered[filtered_index];
		this->adopted_one_by_one->addItem(QString::fromStdString(pet.GetBreed() + " | " + pet.GetName() + " | " + std::to_string(pet.GetAge()) + " | " + pet.GetPhotograph()));
	}
	else
		adopted_one_by_one->clear();
}

void UserWindow::ConnectSignals(){
	connect(next_button, &QPushButton::clicked, this, &UserWindow::NextButtonHandler);
	connect(age_filter_edit, &QLineEdit::textEdited, this, &UserWindow::FilterPetsHandler);
	connect(breed_filter_edit, &QLineEdit::textEdited, this, &UserWindow::FilterPetsHandler);
	connect(open_button, &QPushButton::clicked, this, &UserWindow::OpenPetHandler);
	connect(adopt_button, &QPushButton::clicked, this, &UserWindow::AdoptButtonHandler);
	connect(open_list_button, &QPushButton::clicked, this, &UserWindow::OpenListHandler);
	connect(go_back_button, &QPushButton::clicked, this, &UserWindow::GoBackToMain);
}

void UserWindow::OpenListHandler(){
	this->service.OpenAdoptionList();
}

void UserWindow::AdoptButtonHandler(){
	if (this->adopted_filtered.size() > 0) {
		try {
			Pet adopted_pet = this->adopted_filtered[filtered_index];
			this->service.AdoptPet(adopted_pet);
			this->service.DeletePet(adopted_pet.GetBreed(), adopted_pet.GetName());
			adopted_filtered = this->service.GetYoungDogsOfGivenBreed(given_breed, given_age);
			//this->NextButtonHandler();
			this->NextPet();
			this->PopulateAdoptedList();
		}
		catch (exception) {}
		catch (PetException){}
		catch (RepoException) {}
	}
}

void UserWindow::OpenPetHandler(){
	Pet opened_pet = this->adopted_filtered[filtered_index];
	system(string("start " + opened_pet.GetPhotograph()).c_str());
}

void UserWindow::FilterPetsHandler(){
	QString age = age_filter_edit->text();
	if (!age.isEmpty()) {
		QString breed = breed_filter_edit->text();
		try {
			given_age = age.toInt();
			given_breed = breed.toStdString();
			filtered_index = 0;
			adopted_filtered = this->service.GetYoungDogsOfGivenBreed(breed.toStdString(), age.toInt());
			this->PopulateAdoptedFilteredList();
		}
		catch (exception) {}
		catch (PetException) {}
		catch (RepoException) {}
	}
}

void UserWindow::NextButtonHandler(){
	if (this->adopted_filtered.size() > 0) {
		if (filtered_index == adopted_filtered.size()-1)
			filtered_index = 0;
		else
			filtered_index++;
		this->PopulateAdoptedFilteredList();
	}
}

void UserWindow::NextPet(){
	if (adopted_filtered.size() == 1)
		filtered_index = 0;
	this->PopulateAdoptedFilteredList();
}
