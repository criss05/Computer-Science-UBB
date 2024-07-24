#pragma once

#include <QWidget>
#include "ui_PaintWindow.h"
#include "Star.h"
#include <vector>


class PaintWindow : public QWidget
{
	Q_OBJECT

public:
	PaintWindow(Star star, std::vector<Star> cst, QWidget *parent = nullptr);
	~PaintWindow();

private:
	Ui::PaintWindowClass ui;
	Star star;
	std::vector<Star> cst;

	void paintConstellation();

protected:
	void paintEvent(QPaintEvent* event) override;
};
