#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LifeTracker.h"

class LifeTracker : public QMainWindow
{
	Q_OBJECT

public:
	LifeTracker(QWidget *parent = Q_NULLPTR);

private:
	Ui::LifeTrackerClass ui;
};
