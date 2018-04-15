//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QApplication>
#include <QQmlEngine>
#include <QQuickItem>
#include <QObject>
#include <QQuickWidget>
#include <QQmlContext>
#include <QTimer>
#include <QMetaObject>
#include <QtQuick>
#include <geSG/Scene.h>

#include "Simple_geSGRenderer.h"
#include "ModelLoader.h"
#include "Game.h"
#include <assimp/camera.h>
#include "Camera.h"
#include "CameraControl.h"

using namespace fsg;

class ApplicationControl : public QObject
{
	Q_OBJECT

	QApplication* application;
	QQmlEngine* qmlEngine;
	QQuickItem* guiRoot;
	QQuickWindow* mainWindow;
	Simple_geSGRenderer* renderer;
	ModelLoader* modelLoader = new ModelLoader();

	QTimer* renderingTimer;
	Game* activeGame = nullptr;
	Camera* activeCamera = nullptr;
	CameraControl* cameraControl = nullptr;

	float lastMousePositionX = 0.0f;
	float lastMousePositionY = 0.0f;
	float panSensitivity = 0.5f;
	float rotateSensitivity = 0.5f;
	float zoomSensitivity = 0.5f;

	bool panUpOnNextUpdate = false;
	bool panLeftOnNextUpdate = false;
	bool panDownOnNextUpdate = false;
	bool panRightOnNextUpdate = false;

public:
	explicit ApplicationControl(QApplication* in_app, QQuickWindow* in_win, QQmlEngine* in_eng);

	void SetIcons() const;
	void SetRendering();
	void InitWindow();
	void QtConnect() const;
	void CleanAssets();

	void ActivateRendering() const;
	void StopRendering() const;

	void ConsoleWrite(const QString message) const;
	void LoadSettings() const;

	vector<RenderingObject*> GetObjectsForRendering() const;

	Q_INVOKABLE void NewStandardGame(QString p1_name, int p1_layout, QString p2_name, int p2_layout);

	Q_INVOKABLE void OnMouseEvent(int buttons, float x, float y);
	Q_INVOKABLE void OnWheelEvent(float angleDelta) const;
	Q_INVOKABLE void OnKeyPressed(unsigned int key);
	Q_INVOKABLE void OnKeyReleased(unsigned int key);

public slots:
	void Update() const;

	void GamePause() const;
	void GameContinue() const;
	void GameEnd();

private:
	void HandleKeyboardEvents() const;
};
