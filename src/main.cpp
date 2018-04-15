//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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