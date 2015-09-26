#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "P.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
private:
	P *pw;
};

#endif // MAINWINDOW_H
