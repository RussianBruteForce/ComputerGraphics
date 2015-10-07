#include "Kek.h"

Kek::Kek()
{
	img = nullptr;
//	drawPoint = QPoint(width()/2, height()/2);
	rect = QSize(100, 150);
	painter = new QPainter();

	p1 << QPoint(40, 30)
	   << QPoint(60, 10)
	   << QPoint(80, 30)
	   << QPoint(60, 50);
	p2 << QPoint(30, 0)
	   << QPoint(80, 0)
	   << QPoint(100, 20)
	   << QPoint(100, 70)
	   << QPoint(80, 90)
	   << QPoint(0, 90)
	   << QPoint(30, 70)
	   << QPoint(30, 50)
	   << QPoint(0, 50)
	   << QPoint(0, 30);

	xr = yr = 0;
//	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

//	redraw();
	reset();
}

Kek::~Kek()
{
	delete painter;
	delete img;
}

void Kek::mousePressEvent(QMouseEvent* event)
{
	switch (event->button()) {
	case Qt::RightButton:
		qDebug() << "pressed" << event->pos();
		startPos = event->pos();
		break;
	case Qt::LeftButton:
		aPoint = event->pos();
		break;
	default:
		break;
	}
}

void Kek::mouseMoveEvent(QMouseEvent* event)
{

	if ((event->buttons() & Qt::RightButton)) {
		qDebug() << "moved" << event->pos();
		drawPoint += event->pos() - startPos;
		startPos = event->pos();
	}
	if ((event->buttons() & Qt::LeftButton)) {
//		angle += event->pos().x() - aPoint.x();
		transform.translate(xr, yr);
		transform.rotate(event->pos().x() - aPoint.x());
		transform.translate(-xr, -yr);
		aPoint = event->pos();
	}
	redraw();
}

void Kek::mouseReleaseEvent(QMouseEvent* event)
{
//	QPoint mPoint;
	switch (event->button()) {
	case Qt::RightButton:
		qDebug() << "release" << event->pos();
		drawPoint += event->pos() - startPos;
		break;

	case Qt::LeftButton:
//		angle += event->pos().x() - aPoint.x();
		transform.translate(xr, yr);
		transform.rotate(event->pos().x() - aPoint.x());
		transform.translate(-xr, -yr);
		aPoint = event->pos();
		break;
	default:
		break;
	}
	redraw();
}

void Kek::wheelEvent(QWheelEvent* event)
{
	qDebug() << "wheel";
	qreal ch = 1.05;
	if (event->pixelDelta().y() < 0)
		ch = 2 - ch;

	transform.scale(ch,ch);

//	transform.translate(drawPoint.x(), drawPoint.y());
	redraw();
//	event->accept();
}

void Kek::redraw()
{
	qDebug() << "draw";
	QSize s = size();
	if (img != nullptr)
		delete img;

	QPicture pic;
	img = new QPixmap(s);
	img->fill();
	painter->begin(&pic);
	painter->setPen(QPen(Qt::black));
	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	//transform.translate(xr, yr);
	painter->setTransform(transform);
	painter->drawPolygon(p1);
	painter->drawPolygon(p2);
//	painter->drawRect(QRect(drawPoint, rect));
	painter->end();

	painter->begin(img);
	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	painter->drawPicture(drawPoint, pic);
	painter->end();
	setPixmap(*img);
}

void Kek::xR(int x)
{
	xr = x;
}

void Kek::yR(int y)
{
	yr = y;
}

void Kek::reset()
{
	transform.reset();
	drawPoint = QPoint(width()/2, height()/2);
	redraw();
}

