//----------------------------------------------//
//    Modified by (75%): Pavel Hranáè (xhrana02)    //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
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
        std::vector<RenderingObject*> renderingObjects;
    public:
        explicit Simple_geSGRenderer(QObject * parent = nullptr);

        void SetupGLState() const;
        void SetMatrices(Camera* camera);
        glm::mat4 GetPerspectiveMatrix() const
        {
            return perspectiveMatrix;
        }
        glm::mat4 GetViewMatrix() const
        {
            return viewMatrix;
        }
        int GetWindowWidth() const
        {
            return _qqw->width();
        }
        int GetWindowHeight() const
        {
            return _qqw->height();
        }

        void SetObjects(std::vector<RenderingObject*> newObjects)
        {
            renderingObjects = newObjects;
        }

        void ClearObjects()
        {
            renderingObjects.clear();
        }

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