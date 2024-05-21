#include "AdminWindow.h"
#include "RepoException.h"
#include <qlabel.h>
#include <qlayout.h>
#include <qformlayout.h>
#include <vector>
#include <qmessagebox.h>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>


AdminWindow::AdminWindow(Service& service, QWidget *parent)
	: QWidget(parent), service{ service }
{
	ui.setupUi(this);
	this->initAdminWindow();
	this->ConnectSignals();
	this->PopulatePetList();
}

AdminWindow::~AdminWindow(){}

void AdminWindow::initAdminWindow(){

	
	QVBoxLayout* admin_layout = new QVBoxLayout{this};

	QFormLayout* pets_data = new QFormLayout;
	QLabel* name_label = new QLabel{ "Name" };
	name_edit = new QLineEdit;
	pets_data->addRow(name_label, name_edit);
	QLabel* breed_label = new QLabel{ "Breed" };
	breed_edit = new QLineEdit;
	pets_data->addRow(breed_label, breed_edit);
	QLabel* age_label = new QLabel{ "Age" };
	age_edit = new QLineEdit;
	pets_data->addRow(age_label, age_edit);
	QLabel* photograph_label = new QLabel{ "Photograph" };
	photograph_edit = new QLineEdit;
	pets_data->addRow(photograph_label, photograph_edit);
	admin_layout->addLayout(pets_data);

	QGridLayout* buttons_layout = new QGridLayout;
	add_button = new QPushButton{ "Add" };
	delete_button = new QPushButton{ "Delete" };
	update_button = new QPushButton{ "Update" };
	buttons_layout->addWidget(add_button, 0, 0);
	buttons_layout->addWidget(delete_button, 0, 1);
	buttons_layout->addWidget(update_button, 0, 2);
	admin_layout->addLayout(buttons_layout);

	admin_layout->addSpacing(50);

	pets_list = new QListWidget{};
	admin_layout->addWidget(pets_list);

	go_back_button = new QPushButton{ "Go back" };
	generate_chart = new QPushButton{ "Generate Chart" };
	admin_layout->addWidget(go_back_button);
	admin_layout->addWidget(generate_chart);
	
	setWindowTitle("Admin Mode");
	setWindowIcon(QIcon("admin.png"));
}

void AdminWindow::ConnectSignals() {
	connect(add_button, &QPushButton::clicked, this, &AdminWindow::AddButtonHandler);
	connect(pets_list, &QListWidget::itemClicked, this, &AdminWindow::SelectPetHandler);
	connect(delete_button, &QPushButton::clicked, this, &AdminWindow::DeleteButtonHandler);
	connect(update_button, &QPushButton::clicked, this, &AdminWindow::UpdateButtonHandler);
	connect(go_back_button, &QPushButton::clicked, this, &AdminWindow::GoBackToMain);
	connect(generate_chart, &QPushButton::clicked, this, &AdminWindow::GenerateChartButtonHandler);
}

void AdminWindow::PopulatePetList() {
	this->pets_list->clear();
	this->service.ReadFromFileService();
	std::vector<Pet> pets = this->service.GetAllPets();

	for (auto pet : pets) {
		this->pets_list->addItem(QString::fromStdString(pet.GetBreed() + " | " + pet.GetName() + " | " + std::to_string(pet.GetAge()) + " | " + pet.GetPhotograph()));
	}
}

void AdminWindow::AddButtonHandler() {
	QString name = this->name_edit->text();
	QString breed = this->breed_edit->text();
	QString age = this->age_edit->text();
	QString photograph = this->photograph_edit->text();

	try {
		this->service.AddPet(breed.toStdString(), name.toStdString(), age.toInt(), photograph.toStdString());
		this->PopulatePetList();
	}
	catch (RepoException& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (PetException& error) {
		string error_str = "";
		for (auto e : error.getError()) {
			error_str += e + "\n";
		}
		QMessageBox::critical(this, "Error", QString::fromStdString(error_str));
	}
}

void AdminWindow::DeleteButtonHandler() {
	int row = this->pets_list->currentRow();
	string breed_str, name_str;
	if (row >= 0) {
		Pet clicked_pet = this->service.GetAllPets()[row];
		breed_str = clicked_pet.GetBreed();
		name_str = clicked_pet.GetName();
	}
	else {
		QString name = name_edit->text();
		QString breed = breed_edit->text();
		name_str = name.toStdString();
		breed_str = breed.toStdString();
	}

	try {
		this->service.DeletePet(breed_str, name_str);
		this->PopulatePetList();
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (PetException& error) {
		string error_str = "";
		for (auto e : error.getError())
			error_str += e + "\n";
		QMessageBox::critical(this, "Error", QString::fromStdString(error_str));
	}
}

void AdminWindow::UpdateButtonHandler() {
	QString name = this->name_edit->text();
	QString breed = this->breed_edit->text();
	QString age = this->age_edit->text();
	QString photograph = this->photograph_edit->text();

	try {
		this->service.UpdatePet(breed.toStdString(), name.toStdString(), age.toInt(), photograph.toStdString());
		this->PopulatePetList();
	}
	catch (RepoException& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	catch (PetException& error) {
		string err_str = "";
		for (auto e : error.getError())
			err_str += e + "\n";
		QMessageBox::critical(this, "Error", QString::fromStdString(err_str));
	}
}

void AdminWindow::SelectPetHandler() {
	int row = this->pets_list->currentRow();
	Pet clicked_pet = this->service.GetAllPets()[row];
	this->name_edit->setText(QString::fromStdString(clicked_pet.GetName()));
	this->breed_edit->setText(QString::fromStdString(clicked_pet.GetBreed()));
	this->age_edit->setText(QString::number(clicked_pet.GetAge()));
	this->photograph_edit->setText(QString::fromStdString(clicked_pet.GetPhotograph()));
}

void AdminWindow::GenerateChartButtonHandler(){
	QBarSeries* series = new QBarSeries();
	QBarSet* set = new QBarSet("Pets");
	*set << service.GetNumberPetAge(1, 3)
		<< service.GetNumberPetAge(3, 5)
		<< service.GetNumberPetAge(5, 8)
		<< service.GetNumberPetAge(8, 10)
		<< service.GetNumberPetAge(10, NULL);

	series->setLabelsVisible();
	series->append(set);

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->setTitle("Pets by age");
	chart->setTheme(QChart::ChartThemeBrownSand);
	chart->setAnimationOptions(QChart::AllAnimations);

	QStringList categories;
	categories << "1Y->3Y" << "3Y->5Y" << "5Y->8Y" << "8Y->10Y" << "+10Y";

	QBarCategoryAxis* axis_x = new QBarCategoryAxis();
	axis_x->append(categories);
	chart->addAxis(axis_x, Qt::AlignBottom);
	series->attachAxis(axis_x);

	QValueAxis* axis_y = new QValueAxis();
	chart->addAxis(axis_y, Qt::AlignLeft);
	series->attachAxis(axis_y);

	QChartView* chart_view = new QChartView(chart);
	chart_view->setChart(chart);
	chart_view->setRenderHint(QPainter::Antialiasing);
	chart_view->resize(500, 500);
	chart_view->setWindowTitle("Pets by age");
	chart_view->show();
}
