//----------------------------------------------//
//	Modified by (50%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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