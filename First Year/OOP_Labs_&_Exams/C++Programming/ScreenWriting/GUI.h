#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Repo.h"
#include "WriterModel.h"

class GUI : public QWidget
{
	Q_OBJECT

private:
	Repo& repo;
	Writer writer;
	WriterModel* model;

public:
	GUI(Repo& repo, Writer writer, WriterModel* model, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;

	void AddButtonHandler();
	void AcceptButtonHandler();
	void SavePlotHandler();
	void DevelopButtonHandler();
};
