#include "Map.h"
#include <QPainter>

Map::Map(Service& service, QWidget *parent)
	: QWidget(parent), service(service)
{
	ui.setupUi(this);
	service.RegisterObserver(this);
}

Map::~Map()
{}

void Map::Update(){
	QPainter painter{ this };
	QPen pen{ Qt::white, 1, Qt::SolidLine, Qt::RoundCap };
	painter.setPen(pen);
	QBrush brush{ Qt::cyan, Qt::SolidPattern };
	painter.setBrush(brush);

	for (auto p : service.GetUndeliveredPackages()) {
		int x = p.GetX()+50;
		int y = p.GetY()+50;
		int dim = 25;
		brush.setColor(Qt::cyan);
		painter.setBrush(brush);
		painter.drawEllipse(x, y, dim, dim);
		this->update();
	}
}

void Map::paintEvent(QPaintEvent* event){
	Update();
}
