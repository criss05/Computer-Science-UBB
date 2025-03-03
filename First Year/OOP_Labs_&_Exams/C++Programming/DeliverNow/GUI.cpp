#include "GUI.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

GUI::GUI(Service& service, Courier courier, QWidget *parent)
	: QWidget(parent), service(service),  courier(courier)
{
	ui.setupUi(this);
	service.RegisterObserver(this);
	ui.courier_zone_line_edit->setText(QString::fromStdString("Zona: " + to_string(courier.GetX()) + ", " + to_string(courier.GetY()) + ", " + to_string(courier.GetRadius())));
	Update();
	connect(ui.deliver_push_button, &QPushButton::clicked, this, &GUI::DeliverButtonHandler);
	ComboBoxPopulate();
	connect(ui.streets_box, &QComboBox::textActivated, this, &GUI::ComboBoxHandler);
}

GUI::~GUI()
{}

void GUI::Update(){
	ui.undelivered_packages_list->clear();
	vector<Package> packages = service.GetUndeliveredPackages();
	for (auto p : packages) {
		if (abs(courier.GetX() - p.GetX()) < courier.GetRadius() && abs(courier.GetY() - p.GetY()) < courier.GetRadius())
			ui.undelivered_packages_list->addItem(QString::fromStdString(p.GetRecipient() + " " + to_string(p.GetX()) + " " + to_string(p.GetY())));
		else
			for (string s : courier.GetStreets())
				if (p.GetStreet() == s)
					ui.undelivered_packages_list->addItem(QString::fromStdString(p.GetRecipient() + " " + p.GetStreet()));
			}
}

void GUI::DeliverButtonHandler(){
	string text = ui.undelivered_packages_list->currentItem()->text().toStdString();
	stringstream stream(text);
	string recipient;
	getline(stream, recipient, ' ');
	service.ModifyPackageStatus(recipient);
	service.notify();
}

void GUI::ComboBoxHandler(const QString& text){
	string street = text.toStdString();
	ui.undelivered_packages_list->clear();
	vector<Package> packages = service.GetPackagesFromStreet(street);
	for (auto p : packages) {
		ui.undelivered_packages_list->addItem(QString::fromStdString(p.GetRecipient() + " " + p.GetStreet()));
	}
}

void GUI::ComboBoxPopulate(){
	vector<string> streets = courier.GetStreets();
	for (auto s : streets)
		ui.streets_box->addItem(QString::fromStdString(s));
}
