//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "CameraControl.h"
#include <exception>
#include <math.h>
#include <QQuickWidget>
#include <glm/glm.hpp>
#include <glm/detail/func_trigonometric.hpp>
#include <glm/detail/func_geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Simple_geSGRenderer.h"

using namespace fsg;
using namespace std;
using namespace glm;
using namespace ge::gl;

CameraControl::CameraControl(Camera* inCamera, int mapSize)
{
	if(inCamera == nullptr)
	{
		throw exception(
			"CameraControl.ctor: Invalid camera object.");
	}
	camera = inCamera;

	if(mapSize < 1)
	{
		throw exception(
			"CameraControl.ctor: Invalid map size.");
	}
	positionXMin = -mapSize / 2.f;
	positionXMax =  mapSize / 2.f;
	positionZMin = -mapSize / 2.f;
	positionZMax =  mapSize / 2.f;
}

void CameraControl::Pan(float x, float z)
{
	// Faster panning when zoomed out
	x *= sqrt(distance);
	z *= sqrt(distance);

	positionX +=
		- sinf(radians(rotationX)) * x
		- cosf(radians(rotationX)) * z;

	positionZ +=
		  cosf(radians(rotationX)) * x
		- sinf(radians(rotationX)) * z;

	CheckPositionBounds();
	UpdateCamera();
}

void CameraControl::PanToPosition(float x, float z)
{
	positionX = x;
	positionZ = z;

	CheckPositionBounds();
	UpdateCamera();
}

void CameraControl::Rotate(float x, float y)
{
	rotationX += x;
	rotationY += y;

	CheckRotationBounds();
	UpdateCamera();
}

/**
 * \brief Positive value to zoom in. Negative value to zoom out.
 */
void CameraControl::Zoom(float zoomChange)
{
	distance -= zoomChange;

	CheckDistanceBounds();
	UpdateCamera();
}

void CameraControl::CheckPositionBounds()
{
	if (positionX < positionXMin)
	{
		positionX = positionXMin;
	}
	else
	if (positionX > positionXMax)
	{
		positionX = positionXMax;
	}

	if (positionZ < positionZMin)
	{
		positionZ = positionZMin;
	}
	else
	if (positionZ > positionZMax)
	{
		positionZ = positionZMax;
	}
}

void CameraControl::CheckRotationBounds()
{
	if (rotationX < 0)
	{
		rotationX += 360;
	}
	else
	if (rotationX > 360)
	{
		rotationX -= 360;
	}

	if (rotationY < rotationYMin)
	{
		rotationY = rotationYMin;
	}
	else
	if (rotationY > rotationYMax)
	{
		rotationY = rotationYMax;
	}
}

void CameraControl::CheckDistanceBounds()
{
	if (distance < distanceMin)
	{
		distance = distanceMin;
	}
	else
	if (distance > distanceMax)
	{
		distance = distanceMax;
	}
}

void CameraControl::UpdateCamera() const
{
	camera->LookAtPosition.x = positionX;
	camera->LookAtPosition.y = positionY;
	camera->LookAtPosition.z = positionZ;

	auto correction = cosf(radians(rotationY));

	camera->EyePosition.x = positionX +
		distance * correction *
		cosf(radians(rotationX));
	camera->EyePosition.y = positionY +
		distance * sinf(radians(rotationY));
	camera->EyePosition.z = positionZ +
		distance * correction *
		sinf(radians(rotationX));
}

vec2 CameraControl::CalculateMousePosition(float x, float y, Simple_geSGRenderer* renderer) const
{
	auto winWidth = renderer->GetWindowWidth();
	auto winHeight = renderer->GetWindowHeight();
	auto view = renderer->GetViewMatrix();
	auto projection = renderer->GetPerspectiveMatrix();

	y = winHeight - y - 1;

	auto wc1 = unProject(vec3(x, y, 0.f), view, projection, vec4(0, 0, winWidth, winHeight));
	auto wc2 = unProject(vec3(x, y, 1.f), view, projection, vec4(0, 0, winWidth, winHeight));
	auto dwcy = wc2.y - wc1.y;
	if (abs(dwcy) < 0.0001)
	{
		dwcy = 0.0001;
	}
	double f = wc1.y / dwcy;
	auto x2d = wc1.x - f * (wc2.x - wc1.x );
	auto z2d = wc1.z - f * (wc2.z - wc1.z );

	return vec2(x2d, z2d);
}
