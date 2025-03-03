#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Service.h"

class GUI : public QWidget, public Observer
{
	Q_OBJECT
private:
	Service& service;
	Courier courier;

public:
	GUI(Service& service, Courier courier, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;

	void Update() override;
	void DeliverButtonHandler();
	void ComboBoxHandler(const QString& text);
	void ComboBoxPopulate();
};
