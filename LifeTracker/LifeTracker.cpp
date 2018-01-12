#include "stdafx.h"
#include "LifeTracker.h"
#include <iostream>

Qt::WindowFlags getFramelessWindowFlags()
{
	return Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint
	#ifdef Q_OS_MAC
			| Qt::Window
	#endif
	#ifdef Q_OS_LINUX
			| Qt::X11BypassWindowManagerHint
	#endif
	#if !defined( Q_OS_MAC )
			| Qt::Tool
	#endif
		;
}

void LifeTracker::focusMainInput()
{
	QTimer::singleShot(0, ui.lineEdit_2, SLOT(setFocus()));
	this->activateWindow();
}

LifeTracker::LifeTracker(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowFlags(getFramelessWindowFlags());
	//	setAttribute(Qt::WA_TranslucentBackground, true);
	//	setWindowOpacity(qreal(40) / 100);
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_TranslucentBackground);
	statusBar()->setSizeGripEnabled(false);
	QList<QToolBar *> allToolBars = findChildren<QToolBar *>();
	foreach(QToolBar *tb, allToolBars)
	{
		removeToolBar(tb);
	}
	setGeometry(
		QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignHCenter,
			size(),
			qApp->desktop()->availableGeometry()
		)
	);

	ui.lineEdit_2->installEventFilter(this);

#ifdef Q_OS_WIN
	if (!RegisterHotKey(HWND(winId()), 0, MOD_ALT | MOD_CONTROL, 0x4D))
	{
		QMessageBox::warning(this, "Warning", "Can’t register hotkey ALT + CTRL + M");
	}
#endif

}

bool LifeTracker::eventFilter(QObject* object, QEvent* event)
{
	QLineEdit* edit = qobject_cast<QLineEdit*>(object);

	if (edit != nullptr)
	{
		if (event->type() == QEvent::FocusIn)
		{
			edit->setStyleSheet(QString("background-color: #3B3F45; border: 1px solid #1E92FF; color: #ffffff;"));
		}
		else if (event->type() == QEvent::FocusOut)
		{
			edit->setStyleSheet(QString("background-color: #3B3F45; border: 1px solid #303339; color: #ffffff;"));
		}
	}
	return false;
}

bool LifeTracker::event(QEvent* e)
{
	switch (e->type())
	{
	case QEvent::WindowActivate:
		break;

	case QEvent::WindowDeactivate:
		hide();
		break;

	case QEvent::KeyPress:
		QKeyEvent* key = dynamic_cast<QKeyEvent*>(e);
		if (key->key() == Qt::Key_Escape) hide();
		break;
	};

	return QMainWindow::event(e);
}

bool LifeTracker::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	Q_UNUSED(eventType);
	Q_UNUSED(result);
	MSG *msg = static_cast<MSG*>(message);
	if (msg->message == WM_HOTKEY)
	{
		show();
		focusMainInput();
	}
	return false;
}