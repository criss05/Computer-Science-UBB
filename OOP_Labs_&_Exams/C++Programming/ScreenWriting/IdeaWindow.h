#pragma once

#include <QWidget>
#include "ui_IdeaWindow.h"
#include "Idea.h"

class IdeaWindow : public QWidget
{
	Q_OBJECT
private:
	Idea idea;

public:
	IdeaWindow(Idea idea, QWidget *parent = nullptr);
	~IdeaWindow();

private:
	Ui::IdeaWindowClass ui;

	void SaveButtonHandler();
};
