#pragma once

#include <QDialog>
#include "ui_ClientRepoType.h"

class ClientRepoType : public QDialog
{
	Q_OBJECT

public:
	ClientRepoType(QWidget *parent = nullptr);
	~ClientRepoType();

private:
	Ui::ClientRepoTypeClass ui;

signals:
	void Format_Chosen(const QString& format);
};
