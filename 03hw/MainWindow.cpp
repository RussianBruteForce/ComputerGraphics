#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  scene{QRect{QPoint{-400,-300}, QSize{800,600}}}
{
	sceneView = new QGraphicsView(&scene, this);
	setCentralWidget(sceneView);
}

MainWindow::~MainWindow()
{

}
