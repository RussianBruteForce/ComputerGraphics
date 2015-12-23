#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Window.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();


private slots:
	void on_actionQuit_triggered();

private:
	Ui::MainWindow *ui;
	Window *w;
};

#endif // MAINWINDOW_H
