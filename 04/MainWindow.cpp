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
	l->redraw();
	setCentralWidget(l);
	auto flags = Qt::Tool;
	QWidget::setWindowFlags(flags);
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
	default:
		break;
	}
}
