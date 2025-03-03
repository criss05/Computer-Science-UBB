#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a89solution.h"

class a89solution : public QMainWindow
{
    Q_OBJECT

public:
    a89solution(QWidget *parent = nullptr);
    ~a89solution();

private:
    Ui::a89solutionClass ui;
};
