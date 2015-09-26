#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	pw = new P(this);
	setCentralWidget(pw);
}

MainWindow::~MainWindow()
{

}
