#ifndef P_H
#define P_H

#include <QWidget>
#include <QPainter>
#include <QSharedPointer>
#include <QDebug>

class P : public QWidget
{
	Q_OBJECT
public:
	explicit P(QWidget *parent = 0)  : QWidget(parent),
		p(new QPainter())
	{
		const int round = 10;
		const int headR = 15;
		const QRect body(QPoint(), QSize(110, 30));
		// глазик у нас дургим цветом, его будем рисовать отдельно
		eye = QRect(body.topLeft() - QPoint(headR*1.1, headR*1.05),
			    QSize(6,4));
		const QSize legSize(10, 55);
		const QRect legL(body.bottomLeft() - QPoint(0, round),
			   legSize);
		const QRect legR(body.bottomRight() - QPoint(legSize.width(), round),
			   legSize);
		const QRect hornBoundingRect(body.topLeft(),
					     QSize(round*2, round*2));

		bull.setFillRule(Qt::WindingFill);

		//тело
		bull.addRoundRect(body, round);

		//голова
		bull.moveTo(body.topLeft() - QPoint(headR, headR)/2);
		bull.addEllipse(bull.currentPosition(), headR, headR);

		//ноги
		bull.addRect(legL);
		bull.addRect(legR);

		//хвост
		bull.moveTo(body.topRight());

		bull.cubicTo(body.topRight() + QPoint(20, 0),
			     body.topRight() + QPoint(10, 20),
			     body.topRight() + QPoint(20, 40));

		bull.cubicTo(body.topRight() + QPoint(0, 10),
			     body.topRight() + QPoint(10, 20),
			     body.topRight());
		//рожки
		bull.moveTo(body.topLeft() - QPoint(headR*2, headR*2));
		bull.arcTo(hornBoundingRect, 90+45, 30);
	}
signals:

public slots:

protected:
	void paintEvent(QPaintEvent *event);

private:
	QSharedPointer<QPainter> p;
	QPainterPath bull;
	QRect eye;
};

#endif // P_H
