#pragma once

#include <QWidget>
#include "ui_Map.h"
#include "Observer.h"
#include "Package.h"
#include "Service.h"

class Map : public QWidget, public Observer
{
	Q_OBJECT

private:
	Service& service;

public:
	Map(Service& service, QWidget *parent = nullptr);
	~Map();

private:
	Ui::MapClass ui;
	void Update() override;

protected:
	void paintEvent(QPaintEvent* event) override;
};
