#include "GUI.h"
#include <qlabel.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <vector>
#include <qmessagebox.h>
#include "RepoException.h"


GUI::GUI(Service& service, QWidget* parent) : QWidget{ parent }, service{ service } {
	this->InitGui();
	admin_window = new AdminWindow{ service };
	user_window = new UserWindow{ service };
	this->ConnectSignals();
}

void GUI::InitGui(){
	QVBoxLayout* main_layout = new QVBoxLayout{ this };

	admin_mode_button = new QPushButton{ "Admin Mode" };
	user_mode_button = new QPushButton{ "User Mode" };
	exit_main_button = new QPushButton{ "Exit" };
	
	main_layout->addWidget(admin_mode_button);
	main_layout->addWidget(user_mode_button);
	main_layout->addWidget(exit_main_button);

	setWindowTitle("Keep calm and adopt a pet");
	setWindowIcon(QIcon("dog.png"));
	resize(400, 300);
}

void GUI::AdminWindowHandler() {
	connect(admin_window, &AdminWindow::Go_back_to_main, this, &GUI::ShowMain);
	admin_window->show();
	this->hide();
}

void GUI::UserWindowHandler() {
	connect(user_window, &UserWindow::Go_back_to_main, this, &GUI::ShowMain);
	user_window->show();
	this->hide();
}

void GUI::ConnectSignals(){
	connect(admin_mode_button, &QPushButton::clicked, this, &GUI::AdminWindowHandler);
	connect(user_mode_button, &QPushButton::clicked, this, &GUI::UserWindowHandler);
	connect(exit_main_button, &QPushButton::clicked, this, &QApplication::quit);
}

void GUI::ShowMain(){
	show();
	if (user_window->isVisible())
		user_window->hide();
	if (admin_window->isVisible())
		admin_window->hide();
}
