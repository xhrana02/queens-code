//----------------------------------------------//
//	Modified by (25%): Pavel Hran�� (xhrana02)	//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
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