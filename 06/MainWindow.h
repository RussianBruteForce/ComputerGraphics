#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "Kek.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void changeEvent(QEvent *e);

private slots:

	void on_actionClear_2_triggered();

	void on_actionQuit_triggered();

private:
	Ui::MainWindow *ui;
	Kek *l;
};

#endif // MAINWINDOW_H
