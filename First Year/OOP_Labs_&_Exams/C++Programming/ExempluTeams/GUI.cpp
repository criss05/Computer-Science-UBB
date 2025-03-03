#include "GUI.h"
#include <qmessagebox.h>
#include <exception>

using namespace std;

GUI::GUI(Service& service, User user, QWidget *parent)
	: QWidget(parent), service(service), user(user)
{
	ui.setupUi(this);

	service.RegisterObserver(this);

	connect(ui.add_button, &QPushButton::clicked, this, &GUI::AddButtonHandler);
	connect(ui.remove_button, &QPushButton::clicked, this, &GUI::RemoveButtonHandler);
	connect(ui.resolve_button, &QPushButton::clicked, this, &GUI::ResolveButtonHandler);

	service.notify();
}

GUI::~GUI()
{}

void GUI::update(){
	ui.issues_list->clear();
	for (auto i : service.GetIssuesSorted()) {
		ui.issues_list->addItem(QString::fromStdString(i.GetDescription() + ";" + i.GetStatus() + ";" + i.GetReporter() + ";" + i.GetSolver()));
	}
}

void GUI::AddButtonHandler(){
	QString description = ui.description_line_edit->text();
	if (user.GetType() != "Tester") {
		QMessageBox::critical(this, "Error", QString::fromStdString("Only testers can report issue!"));
		return;
	}
	try {
		service.AddIssue(description.toStdString(), "open", user.GetName(), "none");
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	this->service.notify();
}

void GUI::RemoveButtonHandler(){
	try {
		int row = ui.issues_list->currentRow();
		Issue issue = service.GetIssuesSorted()[row];
		service.RemoveIssue(issue);
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	service.notify();
}

void GUI::ResolveButtonHandler(){
	if (user.GetType() != "Programmer") {
		QMessageBox::critical(this, "Error", QString::fromStdString("Only programmers can resolve issue!"));
		return;
	}
	try {
		int row = ui.issues_list->currentRow();
		Issue issue = service.GetIssuesSorted()[row];
		service.ResolveIssue(issue, user.GetName());
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	service.notify();
}
