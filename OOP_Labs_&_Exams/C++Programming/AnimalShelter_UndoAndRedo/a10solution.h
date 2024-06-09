#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_a10solution.h"

class a10solution : public QMainWindow
{
    Q_OBJECT

public:
    a10solution(QWidget *parent = nullptr);
    ~a10solution();

private:
    Ui::a10solutionClass ui;
};
