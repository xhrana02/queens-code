//----------------------------------------------//
//	Modified by (50%): Pavel Hranáè (xhrana02)	//
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

using namespace fsg;
using namespace std;
using namespace glm;
using namespace ge::gl;
using namespace ge::sg;
using namespace ge::glsg;

/**
 * Prepares a rendering object before rendering.
 */
void SimpleVT::drawSetup(RenderingObject* object) const
{
	object->PrepareObject(gl);

	auto colorVector = object->GetColor();
	program->set4fv("color", value_ptr(colorVector));

	auto translationMatrix = translate(mat4(1.0f), object->position);
	auto rotationMatrix = rotate(mat4(1.0f), radians(object->rotation), vec3(0.0f, 1.0f, 0.0f));
	auto modelMatrix = translationMatrix * rotationMatrix;
	program->setMatrix4fv("modelMatrix", value_ptr(modelMatrix));

	program->set1f("texRepeat", object->TextureRepeat);
}

/**
 * Use provided shader and draws the provided scene.
 */
void SimpleVT::draw(RenderingObject* object) const
{
	drawSetup(object);

	for (auto model : object->GetGLScene()->scene->models)
	{
		for (auto mesh : model->meshes)
		{
			auto texture = object->GetTexture(mesh.get()).get();
			texture->bind(0);

			auto VAO = object->GetVAO(mesh.get()).get();
			VAO->bind();

			gl->glDrawElements(translateEnum(mesh->primitive), GLsizei(mesh->count),
				translateEnum(mesh->getAttribute(AttributeDescriptor::Semantic::indices)->type), nullptr);

			VAO->unbind();
		}
	}
}

