#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScreenWriting.h"

class ScreenWriting : public QMainWindow
{
    Q_OBJECT

public:
    ScreenWriting(QWidget *parent = nullptr);
    ~ScreenWriting();

private:
    Ui::ScreenWritingClass ui;
};
