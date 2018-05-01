//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QTimer>
#include <QObject>
#include <QQuickWidget>
#include <QMetaObject>
#include <QtQuick>

#include "Simple_geSGRenderer.h"
#include "ModelLoader.h"
#include "Game.h"
#include "Camera.h"
#include "CameraControl.h"


class ApplicationControl : public QObject
{
	Q_OBJECT

	QApplication* application;
	QQmlEngine* qmlEngine;
	QQuickItem* guiRoot;
	QQuickWindow* mainWindow;
	fsg::Simple_geSGRenderer* renderer;
	fsg::ModelLoader* modelLoader = new fsg::ModelLoader();

	QTimer* renderingTimer;
	
	Game* activeGame = nullptr;
	fsg::Camera* activeCamera = nullptr;
	fsg::CameraControl* cameraControl = nullptr;

	float lastMousePositionX = 0.0f;
	float lastMousePositionY = 0.0f;
	float panMouseSensitivity = 0.5f;
	float panKeyboardSensitivity = 0.5f;
	float rotateSensitivity = 0.5f;
	float zoomSensitivity = 0.5f;

	// held keyboard buttons
	bool shiftHeld = false;
	bool panUpOnNextUpdate = false;
	bool panLeftOnNextUpdate = false;
	bool panDownOnNextUpdate = false;
	bool panRightOnNextUpdate = false;
	bool rotateUpOnNextUpdate = false;
	bool rotateLeftOnNextUpdate = false;
	bool rotateRightOnNextUpdate = false;
	bool rotateDownOnNextUpdate = false;
	bool zoomInOnNextUpdate = false;
	bool zoomOutOnNextUpdate = false;

public:
	explicit ApplicationControl(QApplication* in_app, QQuickWindow* in_win, QQmlEngine* in_eng);

	fsg::CameraControl* GetCameraControl() const
	{
		return cameraControl;
	}

	Game* GetGame() const
	{
		return activeGame;
	}

	void SetIcons() const;
	void SetRendering();
	void InitWindow();
	void QtConnect() const;
	void CleanAssets();

	void ActivateRendering() const;
	void StopRendering() const;
	void GetObjectsForRendering() const;

	void ConsoleWrite(const QString message) const;
	void GamePopup(const QString message) const;
	void SetActivePlayer(const QString playerName) const;
	void OnUnitSelected(const QString unitName) const;
	void OnUnitUnselected() const;
	void OnTurnBegin(int turnNumber) const;
	void OnAbilityUsed() const;
	void OnGameOver() const;

	Q_INVOKABLE void LoadSettings();
	Q_INVOKABLE void NewStandardGame(QString p1Name, int p1Code, QString p2Name, int p2Code);
	Q_INVOKABLE void AbilitySelected(int slot) const;
	Q_INVOKABLE void EndTurn() const;

	Q_INVOKABLE void OnMouseMovement(int buttons, float x, float y);
	Q_INVOKABLE void OnMouseClick(int buttons, float x, float y) const;
	Q_INVOKABLE void OnWheelEvent(float angleDelta) const;
	Q_INVOKABLE void OnKeyPressed(unsigned int key);
	Q_INVOKABLE void OnKeyReleased(unsigned int key);

private:
	void HandleKeyboardEvents() const;

public slots:
	void Update() const;

	void GamePause() const;
	void GameContinue() const;
	void GameEnd();
};
