#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include <QPolygon>

class Scene : public QGraphicsScene
{
	int a = 25;
public:
	Scene(QRect sceneRect) :
	QGraphicsScene(sceneRect)
	{
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

		pi1 = addPolygon(p1);
		pi2 = addPolygon(p2);
	}

private:
	QPolygon p1, p2;
	QGraphicsPolygonItem *pi1, *pi2;
	QPoint drawPoint{0,0}, rotatePoint;
	QTransform rt;

	QPoint to_polar(auto phi, auto r, auto incx, auto incy) {
		return QPoint(r * cos(phi) + incx, r * sin(phi) + incy);
	}


protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void wheelEvent(QGraphicsSceneMouseEvent *event);
	void resizeEvent(QGraphicsSceneMouseEvent * event);
};

#endif // SCENE_H
