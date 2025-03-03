#include "GUI.h"
#include <QMessageBox>
#include <exception>
#include "IdeaWindow.h"

using namespace std;

GUI::GUI(Repo& repo, Writer writer, WriterModel* model, QWidget *parent)
	: QWidget(parent), repo(repo), writer(writer), model(model)
{
	ui.setupUi(this);
	ui.ideas_table_view->setModel(model);

	connect(ui.add_push_button, &QPushButton::clicked, this, &GUI::AddButtonHandler);
	connect(ui.accept_push_button, &QPushButton::clicked, this, &GUI::AcceptButtonHandler);
	connect(ui.save_plot_push_button, &QPushButton::clicked, this, &GUI::SavePlotHandler);
	connect(ui.developed_push_button, &QPushButton::clicked, this, &GUI::DevelopButtonHandler);
}

GUI::~GUI()
{}

void GUI::AddButtonHandler(){
	std::string description = ui.description_line_edit->text().toStdString();
	int act = ui.act_line_edit->text().toInt();
	if (description.empty()) {
		QMessageBox::critical(this, "Error", "Description cannot be empty");
		return;
	}
	if(act <1 || act >3){
		QMessageBox::critical(this, "Error", "Act must be between 1 and 3");
		return;
	}
	try {
		repo.AddIdea(Idea(description, "proposed", writer.GetName(), act));
		model->update();
	}catch (exception &e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void GUI::AcceptButtonHandler(){
	if (writer.GetExpertise() != "senior") {
		QMessageBox::critical(this, "Error", "Only senior writers can accept ideas");
		return;
	}
	QModelIndexList selected = this->ui.ideas_table_view->selectionModel()->selectedIndexes();
	if (selected.size() == 0) {
		QMessageBox::critical(this, "Error", "No selection!");
		return;
	}
	int index = ui.ideas_table_view->currentIndex().row();
	Idea& idea = repo.GetIdeas()[index];
	if(idea.GetStatus() != "proposed") {
		QMessageBox::critical(this, "Error", "The idea is already accepted!");
		return;
	}
	idea.SetStatus("accepted");
	model->update();
}

void GUI::SavePlotHandler(){
	repo.SaveIdeas();
}

void GUI::DevelopButtonHandler(){
	vector<Idea> ideas = repo.GetIdeas();
	for (auto i : ideas) {
		if (i.GetStatus() == "accepted" && i.GetCreator() == writer.GetName()) {
			IdeaWindow* window = new IdeaWindow(i);
			window->show();
		}
	}
}
