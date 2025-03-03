#pragma once

#include <QWidget>
#include "ui_UserWindow.h"
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class UserWindow : public QWidget
{
	Q_OBJECT

public:
	UserWindow(Service& service, QWidget* parent = nullptr);
	~UserWindow();

	void initUserWindow();

private:
	void PopulateAdoptedList();
	void PopulateAdoptedFilteredList();
	void ConnectSignals();

	void OpenListHandler();
	void AdoptButtonHandler();
	void OpenPetHandler();
	void FilterPetsHandler();
	void NextButtonHandler();
	void NextPet();

signals:
	void Go_back_to_main();

private slots:
	void GoBackToMain() { emit Go_back_to_main(); }

private:
	Ui::UserWindowClass ui;

	Service& service;

	vector<Pet> adopted_filtered;
	int filtered_index;
	int given_age;
	string given_breed;

	QLineEdit* breed_filter_edit;
	QLineEdit* age_filter_edit;

	QPushButton* adopt_button;
	QPushButton* open_button;
	QPushButton* next_button;

	QListWidget* adopted_one_by_one;

	QListWidget* adopted_list;

	QPushButton* open_list_button;
	QPushButton* go_back_button;
};
