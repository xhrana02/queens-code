//----------------------------------------------//
//	Modified by (25%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include <SimpleVT.h>

#include <glsg/GLScene.h>
#include <geSG/Scene.h>
#include <geGL/VertexArray.h>
#include <geGL/Texture.h>
#include <glsg/EnumToGL.h>
#include <geGL/geGL.h>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace fsg;
using namespace ge::sg;
using namespace ge::glsg;

/**
 * Prepares renderingObjects before rendering.
 */
void SimpleVT::drawSetup()
{
	for (auto object : renderingObjects)
	{
		object->PrepareObject(gl.get());
	}
}

/**
 * Use provided shader and draws the provided scene.
 */
void SimpleVT::draw()
{
	program->use();

	for (auto object : renderingObjects)
	{
		auto colorVector = object->GetColor();
		program->set4fv("color", value_ptr(colorVector));

		auto modelMatrix = translate(mat4(1.0f), object->GetPosition());
		program->setMatrix4fv("model", value_ptr(modelMatrix));

		for (auto model : object->GetGLScene()->scene->models)
		{
			for (auto mesh : model->meshes)
			{
				auto texture = object->GetDiffuseTexture(mesh.get()).get();
				texture->bind(0);

				auto VAO = object->GetVAO(mesh.get()).get();
				VAO->bind();

				gl->glDrawElements(translateEnum(mesh->primitive), GLsizei(mesh->count),
					translateEnum(mesh->getAttribute(AttributeDescriptor::Semantic::indices)->type), nullptr);

				VAO->unbind();
			}
		}
	}
}

void SimpleVT::SetObjects(vector<RenderingObject*> newObjects)
{
	renderingObjects = newObjects;
}

