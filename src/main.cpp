//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "ApplicationControl.h"

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	QQuickWindow mainWindow;
	QQmlEngine qmlEngine;

	make_shared<ApplicationControl*>(new ApplicationControl(&application, &mainWindow, &qmlEngine));

	#ifdef NDEBUG
		FreeConsole();
	#endif

	return application.exec();
}