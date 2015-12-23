#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Tool);

	w = new Window(this);
	setCentralWidget(w);
	w->refill();
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    qApp->exit();
}

