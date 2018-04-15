//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Camera.h"

namespace fsg
{
	class CameraControl
	{
		Camera* camera = nullptr;

		float positionX = 0.0;
		float positionXMin;
		float positionXMax;
		float const positionY = 0.0;
		float positionZ = 0.0;
		float positionZMin;
		float positionZMax;

		float rotationX = 270.0;
		float rotationY = 45.0;
		float const rotationYMin = 10.0;
		float const rotationYMax = 80.0;

		float distance = 5.0;
		float const distanceMin = 1.0;
		float const distanceMax = 10.0;

	public:
		explicit CameraControl(Camera* inCamera, int mapSize);
		void Pan(float x, float z);
		void Rotate(float x, float y);
		void Zoom(float zoomChange);
		void UpdateCamera() const;
	};
}

