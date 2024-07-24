#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include "MyModel.h"
#include "Astronomer.h"
#include "FilterModel.h"

class GUI : public QWidget
{
	Q_OBJECT

private:
	Service& service;
	FilterModel* model;
	Astronomer astronomer;

public:
	GUI(Service& service, FilterModel* model, Astronomer astronomer, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;


	void AddButtonHandler();
	void SearchHandler();
	void ViewConstellationHandler();
};
