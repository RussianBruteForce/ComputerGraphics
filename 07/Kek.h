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


class PEANO {
public:
	QPainter *p;
	int x, y;
	QPoint start;
	int step;

	auto c (const int x, const int y) -> QPoint {
//		if
		auto _x = start.x() + x;
		auto _y = start.y() + y;
		return QPoint(_x, _y);
	}
	auto line (const int a, const int b) -> void {
		p->drawLine(c(x, y), c(x + a, y + b));
		x += a;
		y += b;
	}
	auto A (std::int_fast8_t level) -> void {
		if (level > 0) {
			B(level-1);  line(0,step);
			A(level-1);  line(step, 0);
			A(level-1);  line(0,-step);
			C(level-1);
		}
	}

	auto B (std::int_fast8_t level) -> void {
		if (level > 0) {
			A(level-1);  line(step, 0);
			B(level-1);  line(0, step);
			B(level-1);  line(-step, 0);
			D(level-1);
		}
	}

	auto C (std::int_fast8_t level) -> void {
		if (level > 0) {
			D(level-1);  line(-step,0);
			C(level-1);  line(0,-step);
			C(level-1);  line(step,0);
			A(level-1);
		}
	}

	auto D (std::int_fast8_t level) -> void {
		if (level > 0) {
			C(level-1);  line(0,-step);
			D(level-1);  line(-step,0);
			D(level-1);  line(0,step);
			B(level-1);
		}
	}
};


class Kek : public QLabel
{
 public:
	Kek();
	~Kek();

	void upd();

	void peano(const QPoint& topleft, const QRect &rect);

 protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent * event);

	QColor randomColor();

	QPixmap *img, *tmp;
	bool KEEEEEK{false};
	QPainter *p;
	QPoint start;
};

#endif // KEK_H
