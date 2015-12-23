#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	l = new Kek();

	//void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;

	//centralWidget()->layout()->addWidget(l);
	l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	l->upd();
	setCentralWidget(l);
	setWindowFlags(Qt::Tool);
}

MainWindow::~MainWindow()
{
	delete l;
	delete ui;
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
