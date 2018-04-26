//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "ApplicationControl.h"
#include "GameFactory.h"
#include <iomanip>
#include <thread>

using namespace fsg;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// CTOR, INIT, CLEAN

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
	renderer = new Simple_geSGRenderer(mainWindow);
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

	// MSAA 4x
	auto format = QSurfaceFormat();
	format.setSamples(4);
	mainWindow->setFormat(format);

	QQmlComponent guiComponent(qmlEngine,
		QUrl::fromLocalFile(APP_RESOURCES"/qml/GUI.qml"));

	guiRoot = qobject_cast<QQuickItem*>(guiComponent.create());
	guiRoot->setParentItem(mainWindow->contentItem());
	qDebug() << guiComponent.errors();
	qmlEngine->rootContext()->setContextProperty("ApplicationControl", this);

	mainWindow->show();
}

void ApplicationControl::LoadSettings()
{
	auto settings = guiRoot->findChild<QObject*>("settings");
	auto fullscreen = QQmlProperty::read(settings, "fullscreen").toBool();
	if (fullscreen)
	{
		mainWindow->showFullScreen();
	}
	else
	{
		mainWindow->showNormal();
	}
	rotateSensitivity = QQmlProperty::read(settings, "rotateSensitivity").toDouble() + 0.01;
	panMouseSensitivity = QQmlProperty::read(settings, "panMouseSensitivity").toDouble() + 0.01;
	panKeyboardSensitivity = QQmlProperty::read(settings, "panKeyboardSensitivity").toDouble() + 0.01;
	zoomSensitivity = QQmlProperty::read(settings, "zoomSensitivity").toDouble() + 0.01;
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

////////////////////////////////////////////////////////////////////////////////
// CONNECTIONS TO QML

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

////////////////////////////////////////////////////////////////////////////////
// RENDERING

void ApplicationControl::ActivateRendering() const
{
	renderingTimer->start();
}

void ApplicationControl::StopRendering() const
{
	renderingTimer->stop();
}

/**
* \brief Provides rendering objects to the renderer.
*/
void ApplicationControl::GetObjectsForRendering() const
{
	if(activeGame != nullptr)
	{
		activeGame->GetObjectsForRendering(renderer);
	}
}

////////////////////////////////////////////////////////////////////////////////
// GAME

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
	activeGame = GameFactory::CreateStandardGame(player1, player2, modelLoader, qmlEngine, guiRoot);

	activeCamera = new fsg::Camera();
	cameraControl = new fsg::CameraControl(activeCamera, activeGame->GetMapSize());
	cameraControl->UpdateCamera();

	ActivateRendering();

	ConsoleWrite("... Game setup complete.");
}

void ApplicationControl::AbilitySelected(QString abilityName)
{
	ConsoleWrite("DEBUG: ABILITY SELECTED, NAME = " + abilityName);
}

////////////////////////////////////////////////////////////////////////////////
// MOUSE EVENTS

void ApplicationControl::OnMouseMovement(int buttons, float x, float y)
{
	auto deltaX = x - lastMousePositionX;
	auto deltaY = y - lastMousePositionY;
	lastMousePositionX = x;
	lastMousePositionY = y;
	auto mouseGamePosition = cameraControl->CalculateMousePosition(x, y, renderer);

	activeGame->HandleMouseMovement(mouseGamePosition);

	// LMB held =  buttons       & 1
	// RMB held = (buttons >> 1) & 1
	// MMB held = (buttons >> 2) & 1
	if(((buttons >> 2) & 1) == 1)
	{
		// MMB (Mouse3)
		if (shiftHeld)
		{
			cameraControl->Pan(deltaX / 110 * panMouseSensitivity, deltaY / 110 * panMouseSensitivity);
		}
		else
		{
			cameraControl->Rotate(deltaX / 3 * rotateSensitivity, deltaY / 3 * rotateSensitivity);
		}
	}
}

void ApplicationControl::OnMouseClick(int buttons, float x, float y) const
{
	auto mouseGamePosition = cameraControl->CalculateMousePosition(x, y, renderer);
	// LMB held =  buttons       & 1
	// RMB held = (buttons >> 1) & 1
	// MMB held = (buttons >> 2) & 1
	if((buttons & 1) == 1)
	{
		// LMB (Mouse1)
		activeGame->HandleMouseClick(mouseGamePosition, LMB);
	}
	if(((buttons >> 1) & 1) == 1)
	{
		// RMB (Mouse2)
		activeGame->HandleMouseClick(mouseGamePosition, RMB);
	}
}

void ApplicationControl::OnWheelEvent(float angleDelta) const
{
	// 120 angle delta = 15 degrees = 1 standard wheel step
	cameraControl->Zoom(angleDelta / 120 * zoomSensitivity);
}

////////////////////////////////////////////////////////////////////////////////
// KEYBOARD EVENTS

void ApplicationControl::OnKeyPressed(unsigned int key)
{
	qDebug() << "Key" << key << "pressed.";
	switch(key)
	{
	case 42: // Left shift
		shiftHeld = true;
		break;
	case 54: // Right shift
		shiftHeld = true;
		break;
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
	case 72: // Num8
		rotateUpOnNextUpdate = true;
		break;
	case 75: // Num4
		rotateLeftOnNextUpdate = true;
		break;
	case 77: // Num6
		rotateRightOnNextUpdate = true;
		break;
	case 80: // Num2
		rotateDownOnNextUpdate = true;
		break;
	case 74: // NumMinus-
		zoomOutOnNextUpdate = true;
		break;
	case 78: // NumPlus+
		zoomInOnNextUpdate = true;
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
	case 42: // Left shift
		shiftHeld = false;
		break;
	case 54: // Right shift
		shiftHeld = false;
		break;
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
	case 72: // Num8
		rotateUpOnNextUpdate = false;
		break;
	case 75: // Num4
		rotateLeftOnNextUpdate = false;
		break;
	case 77: // Num6
		rotateRightOnNextUpdate = false;
		break;
	case 80: // Num2
		rotateDownOnNextUpdate = false;
		break;
	case 74: // NumMinus-
		zoomOutOnNextUpdate = false;
		break;
	case 78: // NumPlus+
		zoomInOnNextUpdate = false;
		break;
	default: // Unhandled keys
		break;
	}
}

void ApplicationControl::HandleKeyboardEvents() const
{
	if(panUpOnNextUpdate) {
		cameraControl->Pan(0, panKeyboardSensitivity / 10.0);
	}
	if (panLeftOnNextUpdate) {
		cameraControl->Pan(panKeyboardSensitivity / 10.0, 0);
	}
	if (panDownOnNextUpdate) {
		cameraControl->Pan(0, -panKeyboardSensitivity / 10.0);
	}
	if (panRightOnNextUpdate) {
		cameraControl->Pan(-panKeyboardSensitivity / 10.0, 0);
	}
	if (rotateUpOnNextUpdate) {
		cameraControl->Rotate(0, 1.25 * rotateSensitivity);
	}
	if (rotateLeftOnNextUpdate) {
		cameraControl->Rotate(2.0 * rotateSensitivity, 0);
	}
	if (rotateRightOnNextUpdate) {
		cameraControl->Rotate(-2.0 * rotateSensitivity, 0);
	}
	if (rotateDownOnNextUpdate) {
		cameraControl->Rotate(0, -1.25 * rotateSensitivity);
	}
	if (zoomOutOnNextUpdate) {
		cameraControl->Zoom(-0.2 * zoomSensitivity);
	}
	if (zoomInOnNextUpdate) {
		cameraControl->Zoom(0.2 * zoomSensitivity);
	}
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SLOTS

/**
 * \brief Called every 16 ms to update the camera and the rendered scene.
 */
void ApplicationControl::Update() const
{
	// check if any relevant keys are held
	HandleKeyboardEvents();
	// update the view and perspective (projection) matrix based on camera's values
	renderer->SetMatrices(activeCamera);
	// update the list of rendered objects
	GetObjectsForRendering();
	// force redraw
	mainWindow->update();
}

void ApplicationControl::GamePause() const
{
	StopRendering();
}

void ApplicationControl::GameContinue() const
{
	ActivateRendering();
}

void ApplicationControl::GameEnd()
{
	CleanAssets();
}
