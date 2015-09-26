#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  scene{QRect{QPoint{-300,-300}, QSize{600,600}}}
{
	sceneView = new QGraphicsView(&scene, this);
	setCentralWidget(sceneView);
}

MainWindow::~MainWindow()
{

}
