#ifndef P_H
#define P_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QSharedPointer>
#include <QDebug>
#include <QMouseEvent>
#include <QList>
#include <QImage>

class P : public QLabel
{
	Q_OBJECT

	enum class State {
		quad,
		rects,
		chess,
		mouse
	};

public:
	explicit P(QWidget *parent = 0)  : QLabel(parent),
		p(new QPainter()),
		rectFillColor(Qt::white),
		state(State::mouse)
	{
		mColors << Qt::red
			<< Qt::yellow
			<< Qt::green
			<< QColor(0,255,255)
			<< Qt::blue
			<< Qt::magenta
			<< Qt::black
			<< Qt::white;
	}
signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QSharedPointer<QPainter> p;
	QColor rectFillColor;
	State state;
	QList<QColor> mColors;
	int x_mod = 0, y_mod = 0;
	QImage img;
	QPixmap pmap;
};

#endif // P_H
