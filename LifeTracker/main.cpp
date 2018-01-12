#include "stdafx.h"
#include "LifeTracker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	LifeTracker life_tracker;
	life_tracker.hide();
	return application.exec();
}
