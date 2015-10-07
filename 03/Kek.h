#ifndef KEK_H
#define KEK_H

#include <QWidget>
#include <QMouseEvent>
#include <QTransform>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QPolygon>
#include <QPicture>

class Kek : public QLabel
{
public:
	Kek();
	~Kek();

	void redraw();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

private:
	QPixmap *img;
	QSize rect;
	QTransform transform;
	QPoint startPos, drawPoint, aPoint;
	QPainter *painter;
	QPolygon p1, p2;
	int xr, yr;


public slots:
	void xR(int x);
	void yR(int y);
	void reset();
};

#endif // KEK_H
