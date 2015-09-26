#include "P.h"

void P::paintEvent(QPaintEvent*)
{
	auto center = QPoint(width()/2, height()/2);
	qDebug() << "PEvent" << center;
	p->begin(this);

//	p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	const QSize rectSize(10, 10);


	switch (state) {
	case P::State::mouse:
//		p->setBrush(rectFillColor);

//		p->drawRect(QRect(QPoint(center.x() - rectSize.width()/2,
//					 center.y() - rectSize.height()/2),
//				  rectSize));

		p->drawImage(QRect(QPoint(center.x() - 128, center.y() - 128),
				   QSize(256,256)),
			     img);
		break;
	case P::State::quad:
		break;
	case P::State::rects:
		break;
	case P::State::chess:
		break;
	}

	p->end();
}

void P::mousePressEvent(QMouseEvent* event)
{

}

void P::mouseMoveEvent(QMouseEvent* event)
{
	auto vx = event->y();
	auto vy = event->x();
	auto sub = height()/255;
	x_mod = vx/sub;
	y_mod = vy/sub;
	//qDebug() << pixmap()->size();

	//pmap = *pixmap();
	//QPainter painter(&pmap);
	//painter.fillRect(0,0, width(),height(), Qt::black);
	//painter.end();

	img = QPixmap(256,256).toImage();

	qDebug() << img.size();

	for (int i = 0;  i <= 255; i++)
		for (int j = 0;  j <= 255; j++)
			img.setPixel(j,i,
				      qRgb(i-x_mod, j-y_mod, (i+j)/2));

	//pmap = QPixmap::fromImage(img);
	update();
	//setPixmap(pmap);
}

void P::mouseReleaseEvent(QMouseEvent* event)
{

}

