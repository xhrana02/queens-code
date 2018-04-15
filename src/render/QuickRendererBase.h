#pragma once

#include <QObject>
#include <QQuickWindow>


/**
 * This class provides basic setup for rendering in Qt Quick. It is intended to use with QQuickWindow.
 * For rendering just subclass from this and reimplement virtual functions you need. You should set
 * parent to window you want to render to. The connections are automaticaly made when calling setParentWindow.
 * Old connections are disconected and new ones are created when the argument is not null.
 */
class QuickRendererBase : public QObject
{
   Q_OBJECT
public:
	explicit QuickRendererBase(QObject * parent = nullptr);

	void setParentWindow(QQuickWindow * qqw);
	QQuickWindow *parentWindow() const { return _qqw; }
public slots:
	virtual void beforeRendering();
	virtual void onOGLContextCreated(QOpenGLContext * context);
	virtual void onSceneGraphInvalidated();
	virtual void onFrameSwapped();
protected:
	QQuickWindow *_qqw;
};