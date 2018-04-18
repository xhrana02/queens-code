//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Camera.h"
#include <geGL/OpenGLContext.h>

using namespace glm;
using namespace ge::gl;

namespace fsg
{
	class CameraControl
	{
		Camera* camera = nullptr;

		float positionX = 0;
		float positionXMin;
		float positionXMax;
		float const positionY = 0.5;
		float positionZ = 0;
		float positionZMin;
		float positionZMax;

		float rotationX = 270;
		float rotationY = 50;
		float const rotationYMin = 15;
		float const rotationYMax = 85;

		float distance = 7;
		float const distanceMin = 2;
		float const distanceMax = 12;

	public:
		explicit CameraControl(Camera* inCamera, int mapSize);
		void Pan(float x, float z);
		void Rotate(float x, float y);
		void Zoom(float zoomChange);
		void UpdateCamera() const;
		vec2 CalculateMousePosition(float x, float y, int winWidth, int winHeight, Context* gl) const;
	};
}

