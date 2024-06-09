#pragma once
#include <qwidget.h>
#include "Service.h"
#include "AdminWindow.h"
#include "UserWindow.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget {
	Q_OBJECT

private:
	Service& service;

	AdminWindow* admin_window;
	UserWindow* user_window;

	QPushButton* admin_mode_button;
	QPushButton* user_mode_button;
	QPushButton* back_admin_button;
	QPushButton* back_user_button;
	QPushButton* exit_main_button;


public:
	GUI(Service& service, QWidget* parent = nullptr);

private:
	void InitGui();
	void AdminWindowHandler();
	void UserWindowHandler();

	void ConnectSignals();
	void ShowMain();
};
