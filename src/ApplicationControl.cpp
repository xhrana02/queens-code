//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "ApplicationControl.h"
#include "GameFactory.h"
#include <iomanip>

/**
 * \brief Constructor for application control class.
 * \param in_app Application created in main.cpp
 * \param in_win Window created in main.cpp
 * \param in_eng Qml engine created in main.cpp
 */
ApplicationControl::ApplicationControl(QApplication* in_app, QQuickWindow* in_win, QQmlEngine* in_eng)
{
	application = in_app;
	mainWindow = in_win;
	qmlEngine = in_eng;

	SetIcons();
	SetRendering();
	InitWindow();
	QtConnect();
	LoadSettings();

	ConsoleWrite("Application started\n: ");
}

void ApplicationControl::SetIcons() const
{
	mainWindow->setIcon(QIcon(APP_RESOURCES"/qricon.ico"));
}

void ApplicationControl::SetRendering()
{
	renderer = new fsg::Simple_geSGRenderer(mainWindow);
	renderingTimer = new QTimer(this);
	connect(renderingTimer, SIGNAL(timeout()), this, SLOT(Update()));
	renderingTimer->setSingleShot(false);
	renderingTimer->setInterval(16);
}


/**
 * \brief Main initialization part of application control class (window and qml root element setup).
 */
void ApplicationControl::InitWindow()
{
	application->setOrganizationName("xhrana02");
	application->setApplicationName("Queens Regicide");

	mainWindow->resize(1280, 720);

	mainWindow->setMinimumSize(QSize(960, 540));

	QQmlComponent guiComponent(qmlEngine,
		QUrl::fromLocalFile(APP_RESOURCES"/qml/GUI.qml"));

	guiRoot = qobject_cast<QQuickItem *>(guiComponent.create());
	guiRoot->setParentItem(mainWindow->contentItem());
	qDebug() << guiComponent.errors();
	qmlEngine->rootContext()->setContextProperty("ApplicationControl", this);

	mainWindow->show();
}


/**
 * \brief Second initialization part of application control class (connections to qml).
 */
void ApplicationControl::QtConnect() const
{
	connect(qmlEngine, SIGNAL(quit()), application, SLOT(quit()));
	connect(guiRoot, SIGNAL(fullscreen()), mainWindow, SLOT(showFullScreen()));
	connect(guiRoot, SIGNAL(windowed()), mainWindow, SLOT(showNormal()));
	connect(guiRoot, SIGNAL(gamePause()), this, SLOT(GamePause()));
	connect(guiRoot, SIGNAL(gameContinue()), this, SLOT(GameContinue()));
	connect(guiRoot, SIGNAL(gameEnd()), this, SLOT(GameEnd()));
}

/**
 * \brief Cleans some game-specific variables.
 */
void ApplicationControl::CleanAssets()
{
	if (activeGame != nullptr)
	{
		delete activeGame;
		activeGame = nullptr;
	}

	if (activeCamera != nullptr)
	{
		delete activeCamera;
		activeCamera = nullptr;
	}

	if (cameraControl != nullptr)
	{
		delete cameraControl;
		cameraControl = nullptr;
	}

	modelLoader->UnloadAllModels();

	renderer->SetObjects(vector<RenderingObject*>());
}

void ApplicationControl::ActivateRendering() const
{
	renderingTimer->start();
}

void ApplicationControl::StopRendering() const
{
	renderingTimer->stop();
}

/**
 * \brief Sends a custom message to be printed in the in-game console.
 * \param message 
 */
void ApplicationControl::ConsoleWrite(const QString message) const
{
	QVariant returnedValue;
	QMetaObject::invokeMethod(guiRoot, "consoleWrite",
		Q_RETURN_ARG(QVariant, returnedValue),
		Q_ARG(QVariant, message));
}

/**
* \brief Invokes a qml function that loads settings.
*/
void ApplicationControl::LoadSettings() const
{
	QVariant returnedValue;
	QMetaObject::invokeMethod(guiRoot, "loadSettings",
		Q_RETURN_ARG(QVariant, returnedValue));
}

vector<RenderingObject*> ApplicationControl::GetObjectsForRendering() const
{
	if(activeGame == nullptr)
	{
		return {};
	}
	return activeGame->GetObjectsForRendering();
}

/**
 * \brief Creates a new standard game and sets it as active.
 */
void ApplicationControl::NewStandardGame(QString p1_name, int p1_layout, QString p2_name, int p2_layout)
{
	ConsoleWrite("... Game setup started.");

	CleanAssets();

	auto player1 = new Player(p1_name, p1_layout);
	auto player2 = new Player(p2_name, p2_layout);
	ConsoleWrite("... " + player1->GetName() + " vs " + player2->GetName());
	activeGame = GameFactory::CreateStandardGame(player1, player2, modelLoader);

	activeCamera = new fsg::Camera();
	cameraControl = new fsg::CameraControl(activeCamera, activeGame->GetMapSize());
	cameraControl->UpdateCamera();

	ActivateRendering();

	ConsoleWrite("... Game setup complete.");
}

void ApplicationControl::OnMouseEvent(int buttons, float x, float y)
{
	auto deltaX = x - lastMousePositionX;
	auto deltaY = y - lastMousePositionY;
	lastMousePositionX = x;
	lastMousePositionY = y;
	// LMB held =  buttons       & 1
	// RMB held = (buttons >> 1) & 1
	// MMB held = (buttons >> 2) & 1
	if(((buttons >> 1) & 1) == 1)
	{
		cameraControl->Rotate(deltaX / 3 * rotateSensitivity, deltaY / 3 * rotateSensitivity);
	}
	else
	if(((buttons >> 2) & 1) == 1)
	{
		cameraControl->Pan(deltaX / 110 * panSensitivity, deltaY / 110 * panSensitivity);
	}
	auto gameMousePosition = cameraControl->CalculateMousePosition(x, y, mainWindow->width(), mainWindow->height(), renderer->GetGL());
	activeGame->HandleMouseMovement(gameMousePosition);
}

void ApplicationControl::OnWheelEvent(float angleDelta) const
{
	// 120 angle delta = 15 degrees = 1 standard wheel step
	cameraControl->Zoom(angleDelta / 120 * zoomSensitivity);
}

void ApplicationControl::OnKeyPressed(unsigned int key)
{
	qDebug() << "Key" << key << "pressed.";
	switch(key)
	{
	case 17: // W
	case 328: // Up arrow
		panUpOnNextUpdate = true;
		break;
	case 30: // A
	case 331: // Left arrow
		panLeftOnNextUpdate = true;
		break;
	case 31: // S
	case 336: // Down arrow
		panDownOnNextUpdate = true;
		break;
	case 32: // D
	case 333: // Right arrow
		panRightOnNextUpdate = true;
		break;
	default: // Unhandled keys
		break;
	}
}

void ApplicationControl::OnKeyReleased(unsigned int key)
{
	qDebug() << "Key" << key << "released.";
	switch (key)
	{
	case 17: // W
	case 328: // Up arrow
		panUpOnNextUpdate = false;
		break;
	case 30: // A
	case 331: // Left arrow
		panLeftOnNextUpdate = false;
		break;
	case 31: // S
	case 336: // Down arrow
		panDownOnNextUpdate = false;
		break;
	case 32: // D
	case 333: // Right arrow
		panRightOnNextUpdate = false;
		break;
	default: // Unhandled keys
		break;
	}
}

void ApplicationControl::Update() const
{
	HandleKeyboardEvents();
	renderer->SetObjects(GetObjectsForRendering());
	renderer->SetMatrices(activeCamera);
	mainWindow->update();
}

void ApplicationControl::GamePause() const
{
	StopRendering();
	// TODO
}

void ApplicationControl::GameContinue() const
{
	ActivateRendering();
	// TODO
}

void ApplicationControl::GameEnd()
{
	CleanAssets();
}

void ApplicationControl::HandleKeyboardEvents() const
{
	if(panUpOnNextUpdate)
	{
		cameraControl->Pan(0, panSensitivity / 8);
	}
	if (panLeftOnNextUpdate)
	{
		cameraControl->Pan(panSensitivity / 8, 0);
	}

	if (panDownOnNextUpdate)
	{
		cameraControl->Pan(0, -panSensitivity / 8);
	}

	if (panRightOnNextUpdate)
	{
		cameraControl->Pan(-panSensitivity / 8, 0);
	}
}
