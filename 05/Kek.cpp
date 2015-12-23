#include "Kek.h"

Kek::Kek()
{
	img = new QPixmap(size());

	p =new QPainter;
}

Kek::~Kek()
{
	delete p;
	delete img;
}

void Kek::mousePressEvent(QMouseEvent* event)
{
	qDebug() << "click";
	switch (event->button()) {
	case Qt::RightButton:
		break;
	case Qt::LeftButton:
		break;
	default:
		break;
	}
}

void Kek::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::RightButton)) {
	}
	if ((event->buttons() & Qt::LeftButton)) {

	}
	redraw();
}

void Kek::mouseReleaseEvent(QMouseEvent* event)
{
	qDebug() <<"wh";
	switch (event->button()) {
	case Qt::RightButton:
		break;

	case Qt::LeftButton:
		break;
	default:
		break;
	}
	redraw();
}

void Kek::wheelEvent(QWheelEvent* event)
{
	qDebug() << "wheel";
	redraw();
}

void Kek::resizeEvent(QResizeEvent* event)
{
	redraw();
	event->accept();
}

void Kek::redraw()
{
	img->fill();

	p->begin(img);
	p->setPen(QPen(Qt::black));
	p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	QSize center = size()/2;
	p->drawLine(10,100,200,300);
	p->end();
	setPixmap(*img);
}
