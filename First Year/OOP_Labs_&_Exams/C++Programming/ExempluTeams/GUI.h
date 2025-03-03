#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Service.h"
#include "User.h"
#include "Observer.h"

class GUI : public QWidget, public Observer
{
	Q_OBJECT
private:
	Service& service;
	User user;

public:
	GUI(Service& service, User user, QWidget *parent = nullptr);
	~GUI();

	void update() override;

	void AddButtonHandler();
	void RemoveButtonHandler();
	void ResolveButtonHandler();

private:
	Ui::GUIClass ui;


};
