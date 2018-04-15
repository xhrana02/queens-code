//----------------------------------------------//
//	Modified by (75%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QuickRendererBase.h>
#include "Camera.h"
#include "RenderingObject.h"

#include <memory>
#include <glm/glm.hpp>
#include <geGL/OpenGLContext.h>

using namespace ge::gl;

namespace fsg
{
	class SimpleVT;

	class Simple_geSGRenderer : public QuickRendererBase
	{
		Q_OBJECT

	public:
		explicit Simple_geSGRenderer(QObject * parent = nullptr);

		void SetupGLState() const;
		void SetMatrices(Camera* camera);
		void SetObjects(vector<RenderingObject*> newObjects) const;

	public slots:
		void beforeRendering() override;
		void onOGLContextCreated(QOpenGLContext * context) override;

	protected:
		shared_ptr<Context> gl;
		shared_ptr<SimpleVT> VT;

		mat4 perspectiveMatrix;
		mat4 viewMatrix;

   };

}