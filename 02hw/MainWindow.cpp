#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  scene{QRect{QPoint{0,0}, QSize{1000,1000}}}
{
	sceneView = new QGraphicsView(&scene, this);
	setCentralWidget(sceneView);
}

MainWindow::~MainWindow()
{

}
