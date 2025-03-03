#pragma once

#include <QWidget>
#include "ui_AdminWindow.h"
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class AdminWindow : public QWidget
{
	Q_OBJECT

public:
	AdminWindow(Service& service, QWidget *parent = nullptr);
	~AdminWindow();

	void initAdminWindow();

private:
	void PopulatePetList();
	void ConnectSignals();

	void AddButtonHandler();
	void DeleteButtonHandler();
	void UpdateButtonHandler();
	void SelectPetHandler();

	void GenerateChartButtonHandler();

signals:
	void Go_back_to_main();

private slots:
	void GoBackToMain() { emit Go_back_to_main(); }

private:
	Ui::AdminWindowClass ui;

	Service& service;

	QLineEdit* name_edit;
	QLineEdit* breed_edit;
	QLineEdit* age_edit;
	QLineEdit* photograph_edit;

	QPushButton* add_button;
	QPushButton* delete_button;
	QPushButton* update_button;

	QListWidget* pets_list;
	QPushButton* go_back_button;

	QPushButton* generate_chart;
};
