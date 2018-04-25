//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <glm/glm.hpp>

namespace fsg
{
	struct Camera
	{
		glm::vec3 EyePosition;
		glm::vec3 LookAtPosition;
		glm::vec3 UpVector;
		float FOVHorizontal;
		float ClipPlaneNear;
		float ClipPlaneFar;
		Camera()
			: EyePosition(1.f, 1.f, 1.f)
			, LookAtPosition(0.f, 0.f, 0.f)
			, UpVector(0.f, 1.f, 0.f)
			, FOVHorizontal(60.f)
			, ClipPlaneNear(0.5f)
			, ClipPlaneFar(1000.f)
		{}
	};
}
