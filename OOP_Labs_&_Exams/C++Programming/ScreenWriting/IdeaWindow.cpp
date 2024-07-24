#include "IdeaWindow.h"
#include <string>
#include <fstream>

using namespace std;

IdeaWindow::IdeaWindow(Idea idea, QWidget *parent)
	: QWidget(parent), idea(idea)
{
	ui.setupUi(this);
	ui.idea_text_edit->setText(QString::fromStdString(idea.GetDescription()));
	connect(ui.save_push_button, &QPushButton::clicked, this, &IdeaWindow::SaveButtonHandler);
}

IdeaWindow::~IdeaWindow()
{}

void IdeaWindow::SaveButtonHandler()
{
	string developed = ui.idea_text_edit->toPlainText().toStdString();
	ofstream file(idea.GetDescription() + ".txt");
	file << developed;
}
