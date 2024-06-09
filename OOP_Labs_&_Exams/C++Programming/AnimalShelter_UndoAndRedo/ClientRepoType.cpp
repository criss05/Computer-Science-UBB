#include "ClientRepoType.h"
#include <qlayout.h>
#include <qpushbutton.h>

ClientRepoType::ClientRepoType(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QVBoxLayout* layout = new QVBoxLayout{ this };

	QPushButton* csv = new QPushButton{ "CSV" };
	QPushButton* html = new QPushButton{ "HTML" };

	layout->addWidget(csv);
	layout->addWidget(html);

	connect(csv, &QPushButton::clicked, [this]() {emit Format_Chosen("CSV"); accept(); });
	connect(html, &QPushButton::clicked, [this]() {emit Format_Chosen("HTML"); accept(); });
}

ClientRepoType::~ClientRepoType()
{}
