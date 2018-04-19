//----------------------------------------------//
//	Modified by (75%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include "QuickRendererBase.h"
#include "Camera.h"
#include "RenderingObject.h"

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <geGL/geGL.h>
#include <geGL/OpenGLContext.h>
#include <QDebug>

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
		void SetObjects(std::vector<RenderingObject*> newObjects) const;

		ge::gl::Context* GetGL() const
		{
			return gl.get();
		}

	public slots:
		void beforeRendering() override;
		void onOGLContextCreated(QOpenGLContext * context) override;

	protected:
		std::shared_ptr<ge::gl::Context> gl;
		std::shared_ptr<SimpleVT> VT;

		glm::mat4 perspectiveMatrix;
		glm::mat4 viewMatrix;

   };

}