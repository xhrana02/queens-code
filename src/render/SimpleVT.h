//----------------------------------------------//
//	Modified by (25%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <VisualizationTechnique.h>
#include <memory>
#include "RenderingObject.h"

using namespace std;
using namespace ge::gl;

namespace fsg
{
	class SimpleVT : public VisualizationTechnique
	{
		vector<RenderingObject*> renderingObjects;

	public:
		void drawSetup() override;
		void draw() override;

		shared_ptr<Context> gl;
		shared_ptr<Program> program;

		void SetObjects(vector<RenderingObject*> newObjects);
	};
}