#include "Kek.h"

Kek::Kek()
{
	img = nullptr;
	//	drawPoint = QPoint(width()/2, height()/2);
	rect = QSize(100, 150);
	sizeF = 1;
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
		rPoint = aPoint;
		break;
	default:
		break;
	}

	auto currRPoint = rPoint - drawPoint;
	xR(currRPoint.x());
	yR(currRPoint.y());
	qDebug() << "Rcenter" << QPoint(xr, yr) << "\nDraw at  <<" << drawPoint << "click" << rPoint <<"\nDiff" <<  rPoint - drawPoint;
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
		//transform.translate();
		//transform.translate(xr, yr);
		//transform.rotate(event->pos().x() - aPoint.x());
		//transform.translate(-xr, -yr);
		angle = event->pos().x() - aPoint.x();
		//aPoint = event->pos();
		qDebug() << "Rcenter" << QPoint(xr, yr);

	}
	redraw();
}

void Kek::mouseReleaseEvent(QMouseEvent* event)
{
	//	rt.reset();
	//	QPoint mPoint;
	switch (event->button()) {
	case Qt::RightButton:
		drawPoint += event->pos() - startPos;
		break;

	case Qt::LeftButton:
		angle = aPoint.x() - aPoint.x();
		writeRot = true;
		//		transform.translate(xr, yr);
		//		transform.rotate(event->pos().x() - aPoint.x());
		//		transform.translate(-xr, -yr);
		//aPoint = event->pos();
		break;
	default:
		break;
	}
	redraw();
}

void Kek::wheelEvent(QWheelEvent* event)
{
	qDebug() << "wheel";
	double ch = 0.05;
	if (event->pixelDelta().y() < 0){
		ch *= -1;
		qDebug() << "low" << ch;
	}
	sizeF += ch;

	//transform.scale(ch,ch);

	//	transform.translate(drawPoint.x(), drawPoint.y());
	redraw();
	//	event->accept();
}

void Kek::resizeEvent(QResizeEvent* event)
{
	redraw();
	event->accept();
}

void Kek::redraw()
{
	//	qDebug() << "draw";
	QSize s = size();
	if (img != nullptr)
		delete img;

	QPolygon rotatedP1, rotatedP2;
	rotatedP1.fill(QPoint(),p1.size());
	rotatedP2.fill(QPoint(),p2.size());

	auto rotate = [this](auto &p,auto &r,QPoint at,auto angle) {
		for(auto i = 0; i < p.size(); i++) {
			auto point = p[i];
			r[i].setX(((point.x() - at.x()) * cos(angle) +
				   sin(angle)*(point.y() - at.y()))+at.x());
			r[i].setY((-(point.x() - at.x())* sin(angle) +
				   cos(angle)*(point.y() - at.y()))+at.y());
		}
	};

	auto trans = [this](auto &p, auto &r, QPoint at) {
		for(auto i = 0; i < p.size(); i++) {
			r[i].setX(p[i].x()*sizeF +
				  //at.x() +
				  drawPoint.x());
			r[i].setY(p[i].y()*sizeF +
				  //at.y() +
				  drawPoint.y());
		}
	};

	if (writeRot) {
		rotate(p1,p1, QPoint(xr, yr),angle/100);
		rotate(p2,p2, QPoint(xr, yr),angle/100);
	} else {
		qDebug()<< "r" << angle;
		rotate(p1,rotatedP1, QPoint(xr, yr),angle/100);
		rotate(p2,rotatedP2, QPoint(xr, yr),angle/100);
	}
	trans(p1, rotatedP1, QPoint(xr, yr));
	trans(p2, rotatedP2, QPoint(xr, yr));


	//QPicture pic;
	img = new QPixmap(s);
	img->fill();
	//painter->begin(&pic);
	painter->begin(img);
	painter->setPen(QPen(Qt::black));
	painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	//transform.translate(xr, yr);
	//painter->setTransform(transform);

	//painter->drawPolygon(p1);
	//painter->drawPolygon(p2);
	painter->drawPolygon(rotatedP1);
	painter->drawPolygon(rotatedP2);
	//	painter->drawRect(QRect(drawPoint, rect));
	//painter->end();


	//	painter->setTransform(rt);
	//painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	//painter->drawPicture(QPoint(0,0), pic);
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

