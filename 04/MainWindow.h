#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
	Ui::MainWindow *ui;
	Kek *l;
};

#endif // MAINWINDOW_H
