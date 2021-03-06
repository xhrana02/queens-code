//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "ApplicationControl.h"
#include "GameFactory.h"
#include <iomanip>

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
    InitRendering();
    InitWindow();
    QtConnect();
    LoadSettings();

    ConsoleWrite("Application started\n: ");
}

void ApplicationControl::SetIcons() const
{
    mainWindow->setIcon(QIcon(APP_RESOURCES"/qricon.ico"));
}

void ApplicationControl::InitRendering()
{
    renderer = new Simple_geSGRenderer(mainWindow);
    renderingTimer = new QTimer(this);
    connect(renderingTimer, SIGNAL(timeout()), this, SLOT(Update()));
    renderingTimer->setSingleShot(false);
    renderingTimer->setTimerType(Qt::PreciseTimer);
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
    renderer->ClearObjects();

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

void ApplicationControl::OnLoadingStarted() const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onLoadingStarted",
        Q_RETURN_ARG(QVariant, returnedValue));
    application->processEvents();
}

void ApplicationControl::UpdateLoadingProgress(float progress) const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "updateLoadingProgress",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, progress));
    application->processEvents();
}

void ApplicationControl::OnLoadingFinished() const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onLoadingFinished",
        Q_RETURN_ARG(QVariant, returnedValue));
}

void ApplicationControl::GamePopup(const QString message) const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "gamePopup",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, message));
}

void ApplicationControl::SetActivePlayer(const QString playerName) const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "setActivePlayer",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, playerName));
}

void ApplicationControl::OnUnitSelected(const QString unitName) const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onUnitSelected",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, unitName));
}

void ApplicationControl::OnUnitUnselected() const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onUnitUnselected",
        Q_RETURN_ARG(QVariant, returnedValue));
}

void ApplicationControl::OnTurnBegin(int turnNumber, bool isAi) const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onTurnBegin",
        Q_RETURN_ARG(QVariant, returnedValue),
        Q_ARG(QVariant, turnNumber),
		Q_ARG(QVariant, isAi));
}

void ApplicationControl::OnAbilityUsed() const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onAbilityUsed",
        Q_RETURN_ARG(QVariant, returnedValue));
}

void ApplicationControl::OnGameOver() const
{
    QVariant returnedValue;
    QMetaObject::invokeMethod(guiRoot, "onGameOver",
        Q_RETURN_ARG(QVariant, returnedValue));
}

void ApplicationControl::IsAiThinking(bool isThinking) const
{
	QVariant returnedValue;
	QMetaObject::invokeMethod(guiRoot, "isAiThinking",
		Q_RETURN_ARG(QVariant, returnedValue),
		Q_ARG(QVariant, isThinking));
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
void ApplicationControl::NewStandardGame(QString p1Name, int p1Code, QString p2Name, int p2Code)
{
    OnLoadingStarted();
    ConsoleWrite("... Standard game setup started.");
    CleanAssets();
    activeGame = GameFactory::CreateStandardGame(p1Name, p1Code, p2Name, p2Code, this, modelLoader, qmlEngine, guiRoot);
    FinishGameSetup();
}

void ApplicationControl::NewScenarioGame(QString scenarioName)
{
    OnLoadingStarted();
    ConsoleWrite("... " + scenarioName);
    ConsoleWrite("... Scenario game setup started.");
    CleanAssets();
    activeGame = GameFactory::CreateScenarioGame(scenarioName, this, modelLoader, qmlEngine, guiRoot);
    FinishGameSetup();
}

void ApplicationControl::FinishGameSetup()
{
    activeCamera = new Camera();
    cameraControl = new CameraControl(activeCamera, activeGame->GetMapSize());
    cameraControl->UpdateCamera();
    ActivateRendering();
    ConsoleWrite("... Game setup complete.");
    activeGame->StartGame();
    OnLoadingFinished();
    GamePopup(activeGame->GetPlayer1()->GetName() + " vs " + activeGame->GetPlayer2()->GetName());
}

void ApplicationControl::AbilitySelected(int slot) const
{
    activeGame->OnAbilitySelected(slot);
}

void ApplicationControl::EndTurn() const
{
    activeGame->GetActivePlayer()->EndTurn();
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
    case 2: // 1
        activeGame->SelectAbility(1);
        break;
    case 3: // 2
        activeGame->SelectAbility(2);
        break;
    case 4: // 3
        activeGame->SelectAbility(3);
        break;
    case 5: // 4
        activeGame->SelectAbility(4);
        break;
    case 6: // 5
        activeGame->SelectAbility(5);
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
    // execute events that need to be executed every iteration
    activeGame->IterationEvents();
    // check if any relevant keys are held
    HandleKeyboardEvents();
    // update the view and perspective (projection) matrix based on camera's values
    renderer->SetMatrices(activeCamera);
    // update the list of rendered objects
    GetObjectsForRendering();
    // force redraw
	application->processEvents();
}

void ApplicationControl::GamePause() const
{
    activeGame->UnselectUnit();
    StopRendering();
    Update();
}

void ApplicationControl::GameContinue() const
{
    Update();
    ActivateRendering();
}

void ApplicationControl::GameEnd()
{
    StopRendering();
    Update();
    CleanAssets();
}
