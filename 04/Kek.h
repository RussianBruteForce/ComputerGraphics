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
#include <QTimer>

class Kek : public QLabel
{
 public:
	Kek();
	~Kek();

	void redraw();

	void transform(const int n, QVector3D *figure, QVector3D *t_figure) {
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

	void axonom(const int n, QVector3D *figure, QVector3D *proj) {
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

	void perspective(const int n, QVector3D *figure, QVector3D *proj) {
		float alp = ProjectionAlpha;
		float beta = ProjectionBeta;
		float z_ = 0;
		float zk = 400;
		for (int i=0; i<n; i++) {
			proj[i].setZ(figure[i].z() - z_);
			proj[i].setX(figure[i].x()*(zk-z_)/(zk-figure[i].z()));
			proj[i].setY(figure[i].y()*(zk-z_)/(zk-figure[i].z()));
		}
	}

	void draw_figure(QPainter *p, const int n, QVector3D *proj, const int m, QPoint *lines) {
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

	static const int vert_l = 16;
	QVector3D fig_v[vert_l] = {
		{0,0,0}, //0
		{0,2,0},
		{1,2,0},
		{1,0,0},
		{2,0,0}, // 4
		{2,-1,0}, // 5
		{-1,-1,0},
		{-1,0,0}, // 7
		{0,0,-1}, // 0
		{0,2,-1},
		{1,2,-1},
		{1,0,-1},
		{2,0,-1}, // 4
		{2,-1,-1}, // 5
		{-1,-1,-1},
		{-1,0,-1}
	};
	QVector3D fig_t[vert_l], fig_p[vert_l], fig_kek[vert_l];
	static const int edges = 24;
	QPoint fig_e[edges] = {
		{0,1},
		{1,2},
		{2,3},
		{3,4},
		{4,5},
		{5,6},
		{6,7},
		{7,0}, // face
		{8,9},
		{9,10},
		{10,11},
		{11,12},
		{12,13},
		{13,14},
		{14,15},
		{15,8}, // back
		{0,8},
		{1,9},
		{2,10},
		{3,11},
		{4,12},
		{5,13},
		{6,14},
		{7,15}
	};
	float FigureSize = 100.0;
	QVector3D FigurePlace = {0.5, 0 , 0};
	float FigureRotateAlpha = 0.5;
	float FigureRotateBeta = 0.5;
	float ProjectionAlpha = 0.0;
	float ProjectionBeta = 0.0;
	QPoint ProjectionCenter = {400, 300};
	QPixmap *img;
	QPainter *p;
	QTimer t;

	int mov_x = 0, mov_y = 0;
	bool left_button = false, right_button = false;
	int xlPos = 0, ylPos = 0;
	int xmPos = 0, ymPos = 0;
	int rot_x = 0, rot_y = 0;
	double fsize = 0;
public slots:
	void lel();
};

#endif // KEK_H
