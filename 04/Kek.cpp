#include "Kek.h"

Kek::Kek()
{
	img = new QPixmap(size());

	t.setInterval(1000/60);
	connect(&t, &QTimer::timeout, this, &Kek::lel);
	t.start();

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
		right_button = true;
		xmPos = event->pos().x();
		ymPos = event->pos().y();
		fsize = 0;
		break;
	case Qt::LeftButton:
		left_button = true;
		xlPos = event->pos().x();
		ylPos = event->pos().y();
		fsize = 0;
		break;
	default:
		break;
	}
}

void Kek::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::RightButton)) {
		mov_x +=event->pos().x()- xmPos;
		xmPos = event->pos().x();
		mov_y += event->pos().y() - ymPos;
		ymPos = event->pos().y();

	}
	if ((event->buttons() & Qt::LeftButton)) {
		rot_x += event->pos().x() - xlPos;
		xlPos = event->pos().x();
		rot_y += event->pos().y() - ylPos;
		ylPos = event->pos().y();

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
		left_button = false;
		break;
	default:
		break;
	}
	redraw();
}

void Kek::wheelEvent(QWheelEvent* event)
{

	qreal ch = 0.05;
	if (event->angleDelta().y() < 0)
		ch *= -1;

	fsize += ch;
	qDebug() << "wheel" << ch <<event->angleDelta() << event->pixelDelta() ;

	//fsize += event->pixelDelta().y();
	//if (size>32768) size=size-65536;

	redraw();
}

void Kek::resizeEvent(QResizeEvent* event)
{
	redraw();
	event->accept();
}

void Kek::lel()
{
	//qDebug() << "upd";
	rot_x += 1;
	rot_y += 2;
	redraw();
}

void Kek::redraw()
{
	img->fill();

	p->begin(img);
	auto pen = QPen(Qt::red);
	pen.setWidth(2);
	p->setPen(pen);
	p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	QPoint center = QPoint(size().width(), size().height())/2;
	ProjectionCenter = center;
	//auto d = center.x()/2;
	//auto m = center/2;

	FigureRotateAlpha = float(rot_x) / 100.0;
	FigureRotateBeta = float(rot_y) / 100.0;
	FigurePlace.setX( float(mov_x));
	FigurePlace.setY( float(mov_y));
	FigureSize += float(fsize) / 12.0;
	transform(vert_l, fig_v, fig_t);
	axonom(vert_l, fig_t, fig_p);
	perspective(vert_l, fig_p, fig_kek);
	draw_figure(p, vert_l, fig_kek, edges, fig_e);

	p->end();
	setPixmap(*img);
}
