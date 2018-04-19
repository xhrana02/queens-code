//----------------------------------------------//
//	Modified by (50%): Pavel Hran�� (xhrana02)	//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <VisualizationTechnique.h>
#include <memory>
#include "RenderingObject.h"

namespace fsg
{
	class SimpleVT : public VisualizationTechnique
	{
		std::vector<RenderingObject*> renderingObjects;

	public:
		void drawSetup() override;
		void draw() override;

		std::shared_ptr<ge::gl::Context> gl;
		std::shared_ptr<ge::gl::Program> program;

		void SetObjects(std::vector<RenderingObject*> newObjects);
	};
}