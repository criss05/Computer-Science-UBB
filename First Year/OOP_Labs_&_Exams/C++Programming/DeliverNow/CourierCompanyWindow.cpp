#include "CourierCompanyWindow.h"
#include <vector>
#include <string>

using namespace std;

CourierCompanyWindow::CourierCompanyWindow(Service& service, QWidget* parent)
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
	service.RegisterObserver(this);

	Update();
	connect(ui.add_push_button, &QPushButton::clicked, this, &CourierCompanyWindow::AddButtonHandler);
}

CourierCompanyWindow::~CourierCompanyWindow()
{}

void CourierCompanyWindow::Update(){
	ui.packages_list->clear();
	vector<Package> packages = service.GetAllPackages();
	for (auto p : packages) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.GetRecipient() + " " + p.GetStreet() + " " + to_string(p.GetX()) + " " + to_string(p.GetY())));
		ui.packages_list->addItem(item);
		if(p.GetStatus())
			item->setBackground(QBrush("green"));
	}
}

void CourierCompanyWindow::AddButtonHandler(){
	string recipient = ui.recipient_line_edit->text().toStdString();
	string street = ui.street_line_edit->text().toStdString();
	int number = stoi(ui.number_line_edit->text().toStdString());
	int x = stoi(ui.x_line_edit->text().toStdString());
	int y = stoi(ui.y_line_edit->text().toStdString());
	bool status = false;

	service.AddPackages(recipient, street, number, x, y, status);
	service.notify();
}
