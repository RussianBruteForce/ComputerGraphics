#include "MainWindow.h"
#include "Kek.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
//	Kek k;
//	k.show();
	return a.exec();
}
