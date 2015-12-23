#include "Kek.h"

Kek::Kek()
{
	img = new QPixmap(size());

	p = new QPainter;

	qsrand(666);
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
		start = event->pos();
		KEEEEEK = true;

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

	if (KEEEEEK) {
		tmp = new QPixmap(img->copy());
		p->begin(tmp);
		p->setPen(Qt::magenta);
		p->drawRect(QRect(start, event->pos()));
		p->end();
		setPixmap(*tmp);
	} else
		upd();
	event->accept();
}

void Kek::mouseReleaseEvent(QMouseEvent* event)
{
	qDebug() <<"wh";
	switch (event->button()) {
	case Qt::RightButton:
		break;

	case Qt::LeftButton:
		peano(start, QRect(start, event->pos()));
		KEEEEEK = false;
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
	auto newimg = img->copy(QRect(QPoint(0,0), event->size()));
	delete img;
	img = new QPixmap(newimg);
	upd();
	event->accept();
}

QColor Kek::randomColor()
{
	return QColor(qrand()%256,qrand()%256,qrand()%256);
}

void Kek::upd()
{
//	img->fill();

//	p->begin(img);
//	p->setPen(QPen(Qt::black));
//	p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//	QSize center = size()/2;



//	p->end();
	setPixmap(*img);
}

void Kek::peano(const QPoint &topleft, const QRect& rect)
{
	int smallest{rect.height()};
	if (smallest > rect.width())
		smallest = rect.width();

	int level{4};
	int step{smallest/(level*level)};

	p->begin(img);
	p->setPen(randomColor());

	PEANO drawer;
	drawer.step = step;
	drawer.x = 0;
	drawer.y = 0;
	drawer.p = p;
	drawer.start = topleft;

	drawer.A(level);

	p->end();
}







