#include "Window.h"

Window::Window(QWidget *parent) :
	QLabel(parent)
{
	p = new QPainter();
	img = new QImage(size(), QImage::Format_RGB16);
	// Seed the random generator with current time
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

}

Window::~Window()
{
	delete img;
	delete p;
}

void Window::fsdither()
{

	const int dith_size = 4; const int dith_colors = dith_size*dith_size+1;
	const float dith_cstep = (float)255 / (dith_colors-1);

//	for (auto c = 0; c < dith_colors; c++)
//		for(auto i = 0; i < dith_size; i++){
//			QString s;
//			for(auto j = 0; j < dith_size; j++){
//			//	D[c][i][j] = D_[abs(16-c)][i][j];
//				s += QString::number(D_[c][i][j]) + QString(", ");
//			}
//			qDebug() << "{" + s + "},";
//		}


	QRgb P,Ps;
	int r, g, b, x1, y1, r1, g1, b1, x0, y0;
//	const int npt = 5;
//	QPoint apt[npt];
	int cx = img->width();
	int cy = img->height();
//	apt[0].setX((cx-cx/dith_size)/2-1);
//	apt[0].setY((cy-cy/dith_size)/2-1);
//	apt[1].setX((cx+cx/dith_size)/2+1);
//	apt[1].setY((cy-cy/dith_size)/2-1);
//	apt[2].setX((cx+cx/dith_size)/2+1);
//	apt[2].setY((cy+cy/dith_size)/2+1);
//	apt[3].setX((cx-cx/dith_size)/2-1);
//	apt[3].setY((cy+cy/dith_size)/2+1);
//	apt[4] = apt[0];
//	Polyline(hdc,apt,npt);
//	p->begin(img);
//	p->drawPolyline(apt,npt);
//	p->end();
//	upd();
//	QImage img_ = QImage(*img);
	auto img_ = new QImage(*img);
	img_->fill(Qt::white);
	for (int y=0; y<cy; y += dith_size)
		for (int x=0; x<cx; x += dith_size)
		{
			x0 = (cx-cx/dith_size)/2+x/dith_size;
			y0 = (cy-cy/dith_size)/2+y/dith_size;
			P = img->pixel(x0, y0);
			r=(float)qRed(P)/dith_cstep;
			g=(float)qGreen(P)/dith_cstep;
			b=(float)qBlue(P)/dith_cstep;
//			qDebug() << r << g << b;

			for (int i=0; i<dith_size; i++)
				for (int j=0; j<dith_size; j++)
				{
//					qDebug() << i << j;
					x1 = x+i; y1 = y+j;
					r1 = D_[r][i][j]*255; g1 = D_[g][i][j]*255; b1 = D_[b][i][j]*255;
					//qDebug() << D_[r][i][j] << D_[g][i][j] << D_[b][i][j];
					Ps = qRgb(r1,g1,b1);
					img_->setPixel(x1,y1,Ps);
				}
		}
	delete img;
	img = img_;


//	for (auto c = 0; c < dith_colors; c++)
//		for(auto i = 0; i < dith_size; i++){
//			QString s;
//			for(auto j = 0; j < dith_size; j++){
//			//	D[c][i][j] = D_[abs(16-c)][i][j];
//				s += QString::number(D_[c][i][j]) + QString(", ");
//			}
////			qDebug() << "{" + s + "},";
//		}

	upd();
	//qDebug( ) << img->size();
}

void Window::filter()
{
	for (int y=0; y<img->height(); y++)
		for (int x=0; x<img->width(); x++)
		{
			int r=0, g=0, b=0;
			for (int i=i_min; i<=i_max; i++)
				for (int j=j_min; j<=j_max; j++)
				{
					int x1 = x+i, y1 = y+j;
					if ((x1>=0)&&(x1<img->width())&&(y1>=0)&&(y1<img->height()))
					{
						auto P = img->pixel(x1,y1);
						r = r+M[i-i_min][j-j_min]*qRed(P);
						g = g+M[i-i_min][j-j_min]*qGreen(P);
						b = b+M[i-i_min][j-j_min]*qBlue(P);
					}
				}
			auto Ps = qRgb(r/K,g/K,b/K);
			img->setPixel(x,y,Ps);
		}
	upd();
}


void Window::mousePressEvent(QMouseEvent* event)
{
	switch (event->button()) {
	case Qt::RightButton:
		drawCircle(event->pos());
		break;
	case Qt::LeftButton:
		drawSquare(event->pos());
		break;
	default:
		break;
	}
	upd();
	//	delete pixmap;
	//	*pixmap = ;
}

void Window::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << "move";
	if ((event->buttons() & Qt::LeftButton))
		drawCircle(event->pos());
	else if ((event->buttons() & Qt::RightButton))
		drawSquare(event->pos());
	upd();
	//	delete pixmap;
	//	*pixmap = ;
}

void Window::resizeEvent(QResizeEvent* event)
{
	auto newimg = img->copy(QRect(QPoint(0,0), event->size()));
	delete img;
	img = new QImage(newimg);
	upd();
}

void Window::drawSquare(QPoint po)
{
	QPoint pos = po;//QPoint(qrand()%size().width(),qrand()%size().height());
	QSize s = QSize(3 +qrand()%size().width()/10,3+qrand()%size().height()/10);
	QColor c = QColor(qrand()%256,qrand()%256,qrand()%256);
	p->begin(img);
	p->setPen(QPen(c));
	p->setBrush(QBrush(c));
	p->drawRect(QRect(pos, s));
	p->end();
}

void Window::drawCircle(QPoint po)
{
	QPoint pos = po;//QPoint(qrand()%size().width(),qrand()%size().height());
	QSize s = QSize(3 +qrand()%size().width()/10,3+qrand()%size().height()/10);
	QColor c = QColor(qrand()%256,qrand()%256,qrand()%256);
	p->begin(img);
	p->setPen(QPen(c));
	p->setBrush(QBrush(c));
	p->drawEllipse(QRect(pos, s));
	p->end();
}
