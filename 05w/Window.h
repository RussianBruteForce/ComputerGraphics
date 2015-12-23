#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QTime>
#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>

namespace Ui {
class Window;
}

class Window : public QLabel
{
	Q_OBJECT

public:
	explicit Window(QWidget *parent = 0);
	~Window();

public slots:
	void fsdither();
	void refill() {
		img->fill(Qt::white);
		upd();
	}
	void filter();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent * event);

private:
	Ui::Window *ui;
	QImage *img;
	QPainter *p;

	void upd() {
		setPixmap(QPixmap::fromImage(*img));
	}

	void drawSquare(QPoint);
	void drawCircle(QPoint);

	const int D_[17][4][4] = {
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,1}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{0,0,0,0},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{0,0,1,1},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{0,1,1,1},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{1,1,1,1},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{0,0,0,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{1,0,0,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{1,1,0,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,0,1},
			{1,1,1,1}
		},
		{
			{1,1,1,1},
			{1,0,0,1},
			{1,0,1,1},
			{1,1,1,1}
		},
		{
			{1,1,1,1},
			{1,0,1,1},
			{1,0,1,1},
			{1,1,1,1}
		},
		{
			{1,1,1,1},
			{1,1,1,1},
			{1,0,1,1},
			{1,1,1,1}
		},
		{
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1}
		}
	};//, D[dith_colors][dith_size][dith_size];

	int M[5][5] = {
		{ 0,  0, -1,  0,  0},
		{ 0, -1,  1, -1,  0},
		{-1,  1,  4,  1, -1},
		{ 0, -1,  1, -1,  0},
		{ 0,  0, -1,  0,  0}
	};

	int K = -1; int i_min = 0, i_max = 4, j_min = 0, j_max = 4;
};

#endif // WINDOW_H
