#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <cmath>

class Scene : public QGraphicsScene
{
	static constexpr int a = 25;
public:
	Scene(QRect sceneRect) :
	QGraphicsScene(sceneRect)
	{
		QImage img(QSize(sceneRect.width(), sceneRect.height()), QImage::Format_RGB888);
		auto f = [](auto phi) {
			return a*(10.0*sin(phi)*sin(phi)+3.0*cos(phi)*cos(phi));
		};
		for (auto i = -M_PI; i < M_PI; i += M_PI/180/3) {
			auto nc = static_cast<int>(i*100)%256;
			auto point = to_polar(i, f(i), sceneRect.width()/2, sceneRect.height()/2);
			img.setPixel(point, qRgb(nc/2,nc,0));
		}
		addPixmap(QPixmap::fromImage(img));
	}

private:
	QPoint to_polar(auto phi, auto r, auto incx, auto incy) {
		return QPoint(r * cos(phi) + incx, r * sin(phi) + incy);
	}
};

#endif // SCENE_H
