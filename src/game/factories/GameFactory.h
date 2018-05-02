//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Game.h"
#include "ModelLoader.h"

class QQuickItem;
class ApplicationControl;

class GameFactory
{
public:
	static Game* CreateStandardGame(QString p1Name, int p1Code, QString p2Name, int p2Code,
		ApplicationControl* appControl, fsg::ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot);

	static Game* CreateScenarioGame(QString scenarioName,
		ApplicationControl* appControl, fsg::ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot);

private:
	static Game* CreateTrainingDuel(ApplicationControl* appControl, fsg::ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot);
	static Game* CreateChess(ApplicationControl* appControl, fsg::ModelLoader* modelLoader, QQmlEngine* engine, QQuickItem* guiRoot);
};
