#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	l = new Kek();

	//void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;

	//centralWidget()->layout()->addWidget(l);
	//l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setCentralWidget(l);
	l->upd();
	setWindowFlags(Qt::Tool);
}

MainWindow::~MainWindow()
{
	delete l;
	delete ui;
	qDebug() << "lel...";
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
	case QEvent::LanguageChange:
		ui->retranslateUi(this);
		break;
	case QEvent::ActivationChange:
		if (!this->isVisible())
			exit(0);
		break;
	default:
		qDebug() << e->type();
		break;
	}
}


void MainWindow::on_actionClear_2_triggered()
{
    l->clear();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}
