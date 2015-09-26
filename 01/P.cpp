#include "P.h"

void P::paintEvent(QPaintEvent*)
{
	qDebug() << "PEvent" << QPoint(width()/2, height()/2);
	p->begin(this);

	p->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

	p->setBrush(Qt::magenta);
	p->setPen(Qt::black);


	QTransform t;
	t.translate(width() / 2 -bull.boundingRect().width() / 2,
		    height() / 2 - bull.boundingRect().height() / 2);
	t.scale(2, 2);
	p->setTransform(t);

	p->drawPath(bull.simplified());

	p->setBrush(Qt::red);
	p->drawEllipse(eye);

	p->end();
}

