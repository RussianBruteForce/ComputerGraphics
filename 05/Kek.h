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
 public:
	Kek();
	~Kek();

	void redraw();

	void transform(int n, QVector3D *figure, QVector3D *t_figure) {
		float size = FigureSize;
		QVector3D move = FigurePlace ;
		float alp = FigureRotateAlpha , beta = FigureRotateBeta;
		for (int i=0; i<n; i++)
			{
				t_figure[i].setX(size * (figure[i].x() * cos(alp)
							 - figure[i].y() * sin(alp)) + move.x());
				t_figure[i].setY(size * (figure[i].x() * sin(alp) * cos(beta)
							 + figure[i].y() * cos(alp)* cos(beta)
							 - figure[i].z() * sin(beta)) + move.y());
				t_figure[i].setZ(size * (figure[i].x() * sin(alp) * sin(beta)
							 + figure[i].y() * cos(alp)* sin(beta)
							 + figure[i].z() * cos(beta)) + move.z());
			}
	}

	void axonom(int n, QVector3D *figure, QVector3D *proj) {
		float alp = ProjectionAlpha;
		float beta = ProjectionBeta;
		for (int i=0; i<n; i++) {
			proj[i].setX(figure[i].x() * cos(alp) - figure[i].y() * sin(alp));
			proj[i].setY(figure[i].x() * sin(alp) * cos(beta)
				     + figure[i].y() * cos(alp)* cos(beta)
				     - figure[i].z() * sin(beta));
			proj[i].setZ(figure[i].x() * sin(alp) * sin (beta)
				     + figure[i].y() * cos(alp)* sin(beta)
				     + figure[i].z() * cos(beta));
		}
	}

	void draw_figure(QPainter *p, int n, QVector3D *proj, int m, QPoint *lines) {
		int x1,y1, x2,y2;
		QVector3D p1,p2;
		for (int j=0; j<m; j++)
			{
				p1 = proj[lines[j].x()];
				p2 = proj[lines[j].y()];
				x1 = p1.x() + ProjectionCenter.x();
				y1 = p1.y()+ ProjectionCenter.y();
				//MoveToEx(hdc, x1, y1, NULL);
				x2 = p2.x() + ProjectionCenter.x() ;
				y2 = p2.y() + ProjectionCenter.y();
				p->drawLine(x1,y1,x2,y2);
			}
	}
 protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent * event);

	static const int vert_l = 8;
	QVector3D fig_v[8] = {{0,0,0}, {1,0,0}, {1,1,0}, {0,1,0},
			      {0,0,1}, {1,0,1}, {1,1,1}, {0,1,1}};
	QVector3D fig_t, fig_p;
	static const int edges = 12;
	QPoint fig_e[edges] = {{ 0,1}, {1,2}, {2,3}, {3,0},
			       {0,4}, { 1,5}, {2,6}, {3,7},
			       {4,5}, {5,6}, {6,7}, {7,4}};
	float FigureSize = 100.0;
	QVector3D FigurePlace = {0, 0 , 0};
	float FigureRotateAlpha = 0.5;
	float FigureRotateBeta = 0.5;
	float ProjectionAlpha = 0.0;
	float ProjectionBeta = 0.0;
	QPoint ProjectionCenter = {400, 300};
	QPixmap *img;
	QPainter *p;
};

#endif // KEK_H
