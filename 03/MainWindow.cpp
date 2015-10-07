#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	l = new Kek();

	void (QSpinBox:: *signal)(int) = &QSpinBox::valueChanged;

	centralWidget()->layout()->addWidget(l);

	connect(ui->xSpinBox, signal,
		l, &Kek::xR);
	connect(ui->ySpinBox, signal,
		l, &Kek::yR);
	connect(ui->resetButton, &QPushButton::clicked,
		l, &Kek::reset);
	connect(ui->resetButton, &QPushButton::clicked,
		ui->xSpinBox, &QSpinBox::clear);
	connect(ui->resetButton, &QPushButton::clicked,
		ui->ySpinBox, &QSpinBox::clear);
	l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	l->redraw();
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
