#include "PaintWindow.h"
#include <QPainter>

PaintWindow::PaintWindow(Star star, std::vector<Star> cst, QWidget *parent)
	: QWidget(parent), star(star), cst(cst)
{
	ui.setupUi(this);
}

PaintWindow::~PaintWindow()
{}

void PaintWindow::paintConstellation(){
	QPainter painter{ this };
	QPen pen{ Qt::white, 1, Qt::SolidLine, Qt::RoundCap };
	painter.setPen(pen);
	QBrush brush{ Qt::white, Qt::SolidPattern };
	painter.setBrush(brush);

	for (auto s : cst) {
		if (s.GetName() == star.GetName()) {
			brush.setColor(Qt::red);
			painter.setBrush(brush);
		}
		else {
			brush.setColor(Qt::black);
			painter.setBrush(brush);
		}
		painter.drawEllipse(s.GetRA()*5, s.GetDec() *5, s.GetDiameter()+10, s.GetDiameter()+10);
		this->update();
	}
}

void PaintWindow::paintEvent(QPaintEvent* event)
{
	this->paintConstellation();
}
