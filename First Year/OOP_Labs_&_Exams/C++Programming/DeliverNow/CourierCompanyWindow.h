#pragma once

#include <QWidget>
#include "ui_CourierCompanyWindow.h"
#include "Service.h"

class CourierCompanyWindow : public QWidget, public Observer
{
	Q_OBJECT

private:
	Service& service;

public:
	CourierCompanyWindow(Service& service, QWidget *parent = nullptr);
	~CourierCompanyWindow();

private:
	Ui::CourierCompanyWindowClass ui;

	void Update() override;
	void AddButtonHandler();
};
