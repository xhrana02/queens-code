//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
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

