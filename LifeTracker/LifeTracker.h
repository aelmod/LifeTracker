#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LifeTracker.h"

class LifeTracker : public QMainWindow
{
	Q_OBJECT

public:
	void focusMainInput();
	LifeTracker(QWidget *parent = Q_NULLPTR);
	bool eventFilter(QObject* object, QEvent* event);
	bool event(QEvent* e);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	Ui::LifeTrackerClass ui;
};
