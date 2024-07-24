#include "GUI.h"
#include <string>
#include <vector>
#include <qmessagebox.h>
#include "PaintWindow.h"

using namespace std;

GUI::GUI(Service& service, FilterModel* model, Astronomer astronomer, QWidget *parent)
	: QWidget(parent), service(service), model(model), astronomer(astronomer)
{
	ui.setupUi(this);
	ui.stars_table_view->setModel(model);
	connect(ui.add_push_button, &QPushButton::clicked, this, &GUI::AddButtonHandler);
	connect(ui.search_line_edit, &QLineEdit::textChanged, this, &GUI::SearchHandler);
	connect(ui.filter_check_box, &QCheckBox::toggled, this->model, &FilterModel::setFilter);
	connect(ui.view_push_button, &QPushButton::clicked, this, &GUI::ViewConstellationHandler);
}

GUI::~GUI()
{}

void GUI::AddButtonHandler(){
	string name, constellation, Ra, Dec, diameter;
	name = ui.name_line_edit->text().toStdString();
	Ra = ui.Ra_line_edit->text().toStdString();
	Dec = ui.Dec_line_edit->text().toStdString();
	diameter = ui.diameter_line_edit->text().toStdString();
	try {
		service.AddStar(name, astronomer.GetConstellation(), stoi(Ra), stoi(Dec), stoi(diameter));
		model->UpdateModel();
	}
	catch (exception& e) {
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::SearchHandler(){
	ui.searched_list_widget->clear();
	string name = ui.search_line_edit->text().toStdString();
	vector<Star> stars = service.GetStarsByName(name);
	for (auto s : stars) {
		ui.searched_list_widget->addItem(QString::fromStdString(s.GetName() + ", " + s.GetConstellation()));
	}
}

void GUI::ViewConstellationHandler(){
	QModelIndexList selected = this->ui.stars_table_view->selectionModel()->selectedIndexes();
	if (selected.size()==0) {
		QMessageBox::critical(this, "Error", "No selected!");
		return;
	}
	int index = ui.stars_table_view->currentIndex().row();
	Star s = service.GetStars()[index];
	if (ui.filter_check_box->isChecked())
		s = service.GetStarsFromConstellation(astronomer.GetConstellation())[index];
	vector<Star> stars = service.GetStarsFromConstellation(s.GetConstellation());
	PaintWindow* paint = new PaintWindow{ s, stars };
	paint->show();
}
