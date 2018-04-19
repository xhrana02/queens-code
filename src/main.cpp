//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "ApplicationControl.h"

using namespace std;

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	application.setOrganizationName("VUTBR FIT");
	application.setOrganizationDomain("fit.vutbr.cz");
	application.setApplicationName("Queens Regicide");

	QQuickWindow mainWindow;
	QQmlEngine qmlEngine;

	// ApplicationControl needs to exist until the end of the application
	// ReSharper disable once CppNonReclaimedResourceAcquisition
	new ApplicationControl(&application, &mainWindow, &qmlEngine);

	#ifdef NDEBUG
		FreeConsole();
	#endif

	return application.exec();
}