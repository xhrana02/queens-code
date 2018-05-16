//----------------------------------------------//
//    Modified by (75%): Pavel Hranáè (xhrana02)    //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Simple_geSGRenderer.h"
#include "SimpleVT.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <QOpenGLContext>
#include <geCore/Text.h>

using namespace fsg;
using namespace std;
using namespace glm;
using namespace ge::gl;

Simple_geSGRenderer::Simple_geSGRenderer(QObject* parent)
   : QuickRendererBase(parent)
   , gl(nullptr)
   , VT(new SimpleVT())
{
}

void Simple_geSGRenderer::SetupGLState() const
{
   gl->glClearColor(0.53f, 0.81f, 0.98f, 0.0f);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gl->glEnable(GL_DEPTH_TEST);
   gl->glEnable(GL_CULL_FACE);
   gl->glCullFace(GL_BACK);
   gl->glViewport(0, 0, _qqw->width(), _qqw->height());
}

/**
 * Calls update, then sets up the required OGL state and use Visualization technique (VT) to draw.
 * Of course the VT can be written in such way that it sets the OGL state completely. Then it needs
 * to reset the state for Qt to draw its GUI.
 */
void Simple_geSGRenderer::beforeRendering()
{
    SetupGLState();

    VT->program->setMatrix4fv("projectionMatrix", value_ptr(perspectiveMatrix));
    VT->program->setMatrix4fv("viewMatrix", value_ptr(viewMatrix));
    VT->program->set3fv("lightPos", value_ptr(vec3(200.0f, 1000.0f, 100.0f)));
    VT->program->set4fv("lightCol", value_ptr(vec4(1.0f, 1.0f, 0.9f, 1.0f)));

    VT->program->use();
	auto transparentObjects = vector<RenderingObject*>();
    for (auto object : renderingObjects)
    {
		if (object->GetColor().w < 1.0f)
		{
			transparentObjects.push_back(object);
			continue;
		}
        VT->draw(object);
    }
	for (auto object : transparentObjects)
	{
		VT->draw(object);
	}

    _qqw->resetOpenGLState();
}

void Simple_geSGRenderer::onOGLContextCreated(QOpenGLContext* context)
{
    context->makeCurrent(_qqw);

    //init geGL gl context
    init();
    gl = make_shared<Context>();
    VT->gl = gl;

    //load shaders
    string shaderDir(APP_RESOURCES"/shaders/");
    auto draw_vs(make_shared<Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(shaderDir + "draw_vs.glsl")));
    auto draw_fs(make_shared<Shader>(GL_FRAGMENT_SHADER, ge::core::loadTextFile(shaderDir + "draw_fs.glsl")));
    auto prog = make_shared<Program>(draw_vs, draw_fs);
    VT->program = prog;

    context->doneCurrent();
}

/**
 * \brief Sets the view matrix to change camera position.
 */
void Simple_geSGRenderer::SetMatrices(Camera* camera)
{
    if (abs(camera->EyePosition.x - camera->LookAtPosition.x) == 0 &&
        abs(camera->EyePosition.y - camera->LookAtPosition.y) == 0 && 
        abs(camera->EyePosition.z - camera->LookAtPosition.z) == 0)
    {
        throw exception("Simple_geSGRenderer.SetMatrices: Camera contains invalid values.");
    }

    perspectiveMatrix = perspective(
        radians(camera->FOVHorizontal),
        static_cast<float>(GetWindowWidth()) / static_cast<float>(GetWindowHeight()),
        camera->ClipPlaneNear,
        camera->ClipPlaneFar);

    viewMatrix = lookAt(
        camera->EyePosition,
        camera->LookAtPosition,
        camera->UpVector);
}
