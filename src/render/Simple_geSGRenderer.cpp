//----------------------------------------------//
//	Modified by (75%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Simple_geSGRenderer.h"
#include "SimpleVT.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <QOpenGLContext>
#include <geCore/Text.h>

using namespace std;
using namespace fsg;

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

	VT->program->setMatrix4fv("projection", value_ptr(perspectiveMatrix));
	VT->program->setMatrix4fv("view", value_ptr(viewMatrix));

	VT->drawSetup();
	VT->draw();

	_qqw->resetOpenGLState();
}

/**
 * Passes down a new set of rendering objects.
 */
void Simple_geSGRenderer::SetObjects(vector<RenderingObject*> newObjects) const
{
	VT->SetObjects(newObjects);
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
	auto simple_vs(make_shared<Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(shaderDir + "vs.glsl")));
	auto simple_fs(make_shared<Shader>(GL_FRAGMENT_SHADER, ge::core::loadTextFile(shaderDir + "fs.glsl")));
	auto prog = make_shared<Program>(simple_vs, simple_fs);
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
		static_cast<float>(_qqw->width()) / static_cast<float>(_qqw->height()),
		camera->ClipPlaneNear,
		camera->ClipPlaneFar);

	viewMatrix = lookAt(
		camera->EyePosition,
		camera->LookAtPosition,
		camera->UpVector);
}
