#include "stdafx.h"
#include "LifeTracker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LifeTracker w;
	w.show();
	return a.exec();
}
