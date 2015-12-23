#include "Kek.h"

Kek::Kek():
	m{Kek::Mode::drawing}
{
	img = new QImage(size(),QImage::Format_RGB32);

//	p = new QPainter;
}

Kek::~Kek()
{
//	delete p;
	delete img;
}

void Kek::mousePressEvent(QMouseEvent* event)
{
	qDebug() << "click";
	auto p = event->pos();
	auto CP = [] (QPoint p) -> _p {
		return {p.x(),p.y()};
	};
	switch (event->button()) {
	case Qt::RightButton:
		rClick = p;
		if (m == Kek::Mode::bz) {
			bzpts.append(CP(p));
			//X += {0,0};
			//X += {50,100};
			//X += {100,100};
			//X += {150,10};
			//X += {0,0};
			if (bzpts.size() > 1) bz(bzpts, qRgb(200,0,255));
			bzpts.clear();
		}
		break;
	case Qt::LeftButton:
		lClick = p;
		if (m == Kek::Mode::polygon) {
			pts.append(p);
			img->setPixel(p,qRgb(255,255,255));
		}
		if (m == Kek::Mode::bz) {
			bzpts.append(CP(p));
			img->setPixel(p,qRgb(200,200,200));
		}
		break;
	case Qt::MiddleButton:
		switch (m) {
		case Kek::Mode::drawing:
			qDebug() << "now filling";
			m = Kek::Mode::filling;
			break;
		case Kek::Mode::filling:
			qDebug() << "now polygon";
			m = Kek::Mode::polygon;
			break;
		case Kek::Mode::polygon:
			qDebug() << "now filledc";
			m = Kek::Mode::filledc;
			break;
		case Kek::Mode::filledc:
			qDebug() << "now bz";
			pts.clear();
			m = Kek::Mode::bz;
			break;
		case Kek::Mode::bz:
			qDebug() << "now drawing";
			m = Kek::Mode::drawing;
			break;
		default:
			break;
		}

		pts.clear();
		bzpts.clear();
		break;
	default:
		break;
	}
	event->accept();
}

void Kek::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::RightButton)) {
	}
	if ((event->buttons() & Qt::LeftButton)) {

	}
	upd();
	event->accept();
}

void Kek::mouseReleaseEvent(QMouseEvent* event)
{
	qDebug() <<"wh";
	auto p = event->pos();
	switch (event->button()) {
	case Qt::RightButton:
//		auto r = rClick - event->pos();
		switch (m) {
		case Kek::Mode::drawing:
			circle(rClick, (rClick - p).manhattanLength(), qRgb(255,255,255));
			break;
		case Kek::Mode::filling:
			fill(p.x(),p.y(),qRgb(0,255,0),img->pixel(p.x(),p.y()));
			break;
		case Kek::Mode::polygon:
			pts.append(p);
			if (pts.size() > 1) polygon(pts,qRgb(255,255,255));
			pts.clear();
			break;
		default:
			break;
		}
		break;
	case Qt::LeftButton:
		switch (m) {
		case Kek::Mode::drawing:
			line(lClick, p, qRgb(255,255,255));
			break;
		case Kek::Mode::filling:
			fill(p.x(),p.y(),qRgb(255,0,0),img->pixel(p.x(),p.y()));
			break;
		case Kek::Mode::filledc:
			filledCircle(lClick, (lClick - p).manhattanLength(), qRgb(0,0,255));
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	upd();
	event->accept();
}

void Kek::wheelEvent(QWheelEvent* event)
{
	qDebug() << "wheel";
	upd();
	event->accept();
}

void Kek::resizeEvent(QResizeEvent* event)
{
	qDebug() << "resize";
	auto newimg = img->copy(QRect(QPoint(0,0), event->size()));
	delete img;
	img = new QImage(newimg);
	upd();
	event->accept();
}

void Kek::upd()
{
	setPixmap(QPixmap::fromImage(*img));
}

void Kek::line(QPoint p1, QPoint p2, QRgb color)
{
//	bool steep = false;
//	if (abs(p1.x()-p2.x())<abs(p1.y()-p2.y())) { // if the line is steep, we transpose the image
////		std::swap(p1.x(), p1.y());
//		int a = p1.y();
//		p1.setY(p1.x());
//		p1.setX(a);
////		std::swap(p2.x(), p2.y());
//		a = p2.y();
//		p2.setY(p2.x());
//		p2.setX(a);
//		steep = true;
//	    }
//	    if (p1.x()>p2.x()) { // make it left-to-right
////		std::swap(p1.x(), p2.x());
//		int a = p2.x();
//		p2.setX(p1.x());
//		p1.setX(a);
////		std::swap(p1.y(), p2.y());
//		a = p2.y();
//		p2.setY(p1.y());
//		p1.setY(a);
//	    }

//	    for (int x=p1.x(); x<=p2.x(); x++) {
//		float t = (x-p1.x())/(float)(p2.x()-p1.x());
//		int y = p1.y()*(1.-t) + p2.y()*t;
////		qDebug() << x << y;
//		if (x < 0 || y < 0 || x >= img->size().width() || y >= size().height())
//			continue;
//		if (steep) {
//		     img->setPixel(y, x, color); // if transposed, de-transpose
//		} else {
//		     img->setPixel(x, y, color);
//		}
//	    }
	int x1 = p1.x();
	int y1 = p1.y();
	int x2 = p2.x();
	int y2 = p2.y();
	int xerr = 0, yerr = 0;
	int dx = x2 - x1, dy = y2 - y1;
	int incX, incY;
	int d, x, y;
	if (dx > 0) incX = 1;
	else if (dx < 0) incX = -1;
	else incX = 0;
	if (dy > 0) incY = 1;
	else if (dy < 0) incY = -1;
	else incY = 0;
	dx = abs(dx); dy = abs(dy);
	if (dx > dy) d = dx; else d = dy;
	x = x1; y = y1;
	img->setPixel(x, y, color);
	for (int i=0; i<d; i++)
	{
		xerr = xerr + dx;
		yerr = yerr + dy;
		if (xerr > d) { xerr -= d; x += incX; }
		if (yerr > d) { yerr -= d; y += incY; }
		img->setPixel(x, y, color);
	}
}

void Kek::polygon(const QVector<QPoint> pts, QRgb color)
{
	QPoint prev = pts.last();
	for(auto &x: pts) {
		line(prev,x,color);
		prev = x;
	};
}

void Kek::circle(QPoint center, int radius, QRgb color)
{
	auto r2 = (long)radius*(long)radius;
	auto dst = 4*r2;
	int dxt = (double)(radius+0.9)/1.414213562373;
	auto t = 0l;
	auto s = -4*r2*(long)radius;
	auto e = (-s/2)-3*r2;
	auto ca = -6*r2;
	auto cd = -10*r2;
	int x = 0;
	int y = radius;
	img->setPixel(center.x(),center.y()+radius,color);
	img->setPixel(center.x(),center.y()-radius,color);
	img->setPixel(center.x()+radius,center.y(),color);
	img->setPixel(center.x()-radius,center.y(),color);
	for (auto index = 1; index <= dxt; index++)
	{
		x++;
		if (e >= 0) e += t+ca;
		else
		{
			y--;
			e += t-s+cd;
			s += dst;
		}
		t -= dst;
		img->setPixel(center.x()+x,center.y()+y,color);
		img->setPixel(center.x()+y,center.y()+x,color);
		img->setPixel(center.x()+y,center.y()-x,color);
		img->setPixel(center.x()+x,center.y()-y,color);
		img->setPixel(center.x()-x,center.y()-y,color);
		img->setPixel(center.x()-y,center.y()-x,color);
		img->setPixel(center.x()-y,center.y()+x,color);
		img->setPixel(center.x()-x,center.y()+y,color);
	}
}

void Kek::filledCircle(QPoint center, int radius, QRgb color)
{
	auto r2 = (long)radius*(long)radius;
	auto dst = 4*r2;
	int dxt = (double)(radius+0.9)/1.414213562373;
	auto t = 0l;
	auto s = -4*r2*(long)radius;
	auto e = (-s/2)-3*r2;
	auto ca = -6*r2;
	auto cd = -10*r2;
	int x = 0;
	int y = radius;
	img->setPixel(center.x(),center.y()+radius,color);
	img->setPixel(center.x(),center.y()-radius,color);
	img->setPixel(center.x()+radius,center.y(),color);
	img->setPixel(center.x()-radius,center.y(),color);
	line(QPoint(center.x()+radius,center.y()),QPoint(center.x()-radius,center.y()),color);
	for (auto index = 1; index <= dxt; index++)
	{
		x++;
		if (e >= 0) e += t+ca;
		else
		{
			y--;
			e += t-s+cd;
			s += dst;
		}
		t -= dst;
		line(QPoint(center.x()+x,center.y()+y),QPoint(center.x()-x,center.y()+y),color);
		line(QPoint(center.x()+y,center.y()-x),QPoint(center.x()-y,center.y()-x),color);
		line(QPoint(center.x()-x,center.y()-y),QPoint(center.x()+x,center.y()-y),color);
		line(QPoint(center.x()-y,center.y()+x),QPoint(center.x()+y,center.y()+x),color);
		img->setPixel(center.x()+x,center.y()+y,color);
		img->setPixel(center.x()+y,center.y()+x,color);
		img->setPixel(center.x()+y,center.y()-x,color);
		img->setPixel(center.x()+x,center.y()-y,color);
		img->setPixel(center.x()-x,center.y()-y,color);
		img->setPixel(center.x()-y,center.y()-x,color);
		img->setPixel(center.x()-y,center.y()+x,color);
		img->setPixel(center.x()-x,center.y()+y,color);
	}

//	for (long i = -radius; i < radius*2; i++)
//	int dx = x2 - x1; // horizontal offset
//	int dy = y2 - y1; // vertical offset
//	for (int i = -radius; i <= 0; i++)
//		for (int j = -radius; j <= radius; j++)
//	if ( (i*i + j*j) <= (radius*radius) )
//	{
//		//img->setPixel(center.x()+ i,center.y()+ j, color);
//		line(QPoint(center.x()-i,center.y()+j),QPoint(center.x()+i,center.y()+j),color);
//	}
//	circle(center, radius, color);
}

void Kek::fill(const int x, const int y, const QRgb color, const QRgb oldc)
{
	if (x < 0 || y < 0 || x >= img->size().width() || y >= size().height())
		return;
	if (oldc == img->pixel(x,y) && oldc != color) {
		img->setPixel(x,y,color);
		fill(x+1,y,color, oldc);
		fill(x-1,y,color, oldc);
		fill(x,y+1,color, oldc);
		fill(x,y-1,color, oldc);
	}
}

void Kek::bz(QVector<Kek::_p> X, QRgb color)
{
	auto R = X;

	auto PC = [] (_p p) -> QPoint {
		return QPoint(p.x, p.y);
	};

	auto eps = 5e-2;
	auto oldP = PC(X[0]);
	for (auto t = 0.0; t <= 1; t += eps) {
		b(X, R, t);
		line(oldP, PC(R[0]), color);
		oldP = PC(R[0]);
		//img->setPixel(PC(R[0]), color);
	}
}

void Kek::b(QVector<Kek::_p>& P, QVector<Kek::_p>& R, double t)
{
	auto m = P.size() - 1;
	for (auto i = 0; i <= m; i++)
		R[i] = P[i];
	for (auto j = m; j > 0; j--)
		for (auto i = 0; i < j; i++)
		{
			R[i].x += t*(R[i+1].x-R[i].x);
			R[i].y += t*(R[i+1].y-R[i].y);
		}
}

//void Kek::fillb(const int x, const int y, const QRgb color, const QRgb border)
//{
//	if (x < 0 || y < 0 || x >= img->size().width() || y >= size().height())
//		return;
//	if (border != img->pixel(x,y) && color != img->pixel(x,y)) {
//		img->setPixel(x,y,color);
//		fillb(x+1,y, color, border);
//		fillb(x-1,y, color, border);
//		fillb(x,y+1, color, border);
//		fillb(x,y-1, color, border);
//	}
//}
