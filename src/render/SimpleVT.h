//----------------------------------------------//
//	Modified by (50%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <VisualizationTechnique.h>
#include "RenderingObject.h"
#include <memory>
#include <glm/glm.hpp>

namespace fsg
{
	class SimpleVT
	{
		void drawSetup(RenderingObject* object) const;
	public:
		void draw(RenderingObject* object) const;

		std::shared_ptr<ge::gl::Context> gl;
		std::shared_ptr<ge::gl::Program> program;
	};
}
