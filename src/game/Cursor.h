//----------------------------------------------//
//	Author: Pavel Hran�� (xhrana02)				//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>

namespace fsg
{
	class RenderingObject;
}

class Cursor
{
	float rotationPerFrame;
	std::shared_ptr<fsg::RenderingObject> renderingObject;
public:
	explicit Cursor(std::shared_ptr<fsg::RenderingObject> model);
	void Update(float x, float z, float phase) const;

	fsg::RenderingObject* GetRenderingObject() const
	{
		return renderingObject.get();
	}
};

