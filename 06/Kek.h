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
#include <QVector3D>
#include <QPicture>
#include <cmath>

class Kek : public QLabel
{
	enum class Mode {
		drawing,
		filling,
		polygon,
		filledc,
		bz
	};

 public:
	Kek();
	~Kek();

	void upd();
	void line(QPoint p1, QPoint p2, QRgb color);
	void polygon(const QVector<QPoint> pts, QRgb color);
	void circle(QPoint center, int radius, QRgb color);
	void filledCircle(QPoint center, int radius, QRgb color);
	void fill(const int x, const int y, const QRgb color, const QRgb oldc);
//	void fillb(const int x, const int y, const QRgb color, const QRgb border);

	struct _p { int x, y; };

	void bz(QVector<_p> X, QRgb color);
	void b(QVector<_p> &P, QVector<_p> &R, double t);

	void clear() { img->fill(Qt::black); upd(); }

 protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent * event);

	QImage *img;
	//QPainter *p;
	Mode m;

	QPoint lClick, rClick;
	QVector<QPoint> pts;
	QVector<_p> bzpts;
};


#endif // KEK_H
