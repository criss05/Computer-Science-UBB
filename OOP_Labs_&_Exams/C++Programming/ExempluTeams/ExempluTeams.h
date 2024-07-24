#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExempluTeams.h"

class ExempluTeams : public QMainWindow
{
    Q_OBJECT

public:
    ExempluTeams(QWidget *parent = nullptr);
    ~ExempluTeams();

private:
    Ui::ExempluTeamsClass ui;
};
