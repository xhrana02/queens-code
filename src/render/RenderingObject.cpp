//----------------------------------------------//
//	Author (85%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "RenderingObject.h"
#include "GLSceneProcessor.h"
#include "EnumToGL.h"
#include <geGL/VertexArray.h>
#include <geCore/StandardSemanticsNames.h>

using namespace fsg;
using namespace std;
using namespace glm;
using namespace ge::gl;
using namespace ge::sg;
using namespace ge::glsg;

RenderingObject::RenderingObject(shared_ptr<Scene> inModel)
{
	model = inModel;
}

void RenderingObject::SetModel(std::shared_ptr<ge::sg::Scene> newModel)
{
	model = newModel;
	needToUpdateGLScene = true;
}

vec4 RenderingObject::GetColor() const
{
	if (flashing)
	{
		return flashingColor;
	}
	if (selected)
	{
		return highlightColor;
	}
	if (highlighted)
	{
		return fluctuatedColor;
	}
	if (halflighted)
	{
		return halflightColor;
	}
	return normalColor;
}

void RenderingObject::SetColors(vec4 normal, vec4 halflight, vec4 highlight)
{
	normalColor = normal;
	halflightColor = halflight;
	highlightColor = highlight;
}

void RenderingObject::Highlight()
{
	highlighted = true;
}

void RenderingObject::Unhighlight()
{
	highlighted = false;
}

void RenderingObject::Halflight()
{
	halflighted = true;
}

void RenderingObject::Unhalflight()
{
	halflighted = false;
}

void RenderingObject::Select()
{
	selected = true;
}

void RenderingObject::Unselect()
{
	selected = false;
}

void RenderingObject::Fluctuate(float phase)
{
	vec4 baseColor;
	if (halflighted)
	{
		baseColor = halflightColor;
	}
	else
	{
		baseColor = normalColor;
	}

	auto highlightWeight = sin(radians(phase));
	fluctuatedColor =
		highlightColor * highlightWeight +
		baseColor * (1 - highlightWeight);
}

void RenderingObject::SetFlashColor(vec4 flash)
{
	flashingColor = flash;
}

void RenderingObject::StartFlash()
{
	flashing = true;
	SetFlashColor(normalColor);
}

void RenderingObject::EndFlash()
{
	flashing = false;
}

void RenderingObject::PrepareObject(shared_ptr<Context> context)
{
	if(context.get() != glContext.get())
	{
		glContext = context;
		needToUpdateGLScene = true;
	}
	
	if(needToUpdateGLScene)
	{
		updateGLScene();
		needToUpdateGLScene = false;
	}
}

void RenderingObject::updateGLScene()
{
	if(glContext.get() == nullptr)
	{
		cerr << "GL Context not set for an object being accessed." << endl;
	}

	glScene = GLSceneProcessor::processScene(model, glContext);

	for (auto& meshIt : glScene->GLMeshes)
	{
		//mesh geometry
		auto VAO = make_shared<VertexArray>(glContext->getFunctionTable());
		for (auto& glattrib : meshIt.second)
		{
			if (glattrib.attributeDescriptor->semantic == AttributeDescriptor::Semantic::indices)
			{
				VAO->addElementBuffer(glattrib.BO);
			}
			else
			{
				auto attribLocation = semantic2Attribute(glattrib.attributeDescriptor->semantic);
				if (attribLocation != -1)
				{
					VAO->addAttrib(glattrib.BO, attribLocation, glattrib.attributeDescriptor->numComponents,
						translateEnum(glattrib.attributeDescriptor->type), GLsizei(glattrib.attributeDescriptor->stride));
				}
			}
		}
		vaoContainer[meshIt.first] = VAO;

		//material
		auto mat = meshIt.first->material.get();

		for (auto& comp : mat->materialComponents)
		{
			if (comp->getType() == MaterialComponent::ComponentType::IMAGE)
			{
				auto imageComponent = static_cast<MaterialImageComponent*>(comp.get());
				textureContainer[meshIt.first] = glScene->textures[imageComponent];
			}
		}
	}
}

/**
* Internal helper function that returns attribute position for given semantic or -1
* if the attrib is not to be used by this VT.
*/
int RenderingObject::semantic2Attribute(AttributeDescriptor::Semantic semantic)
{
	switch (semantic)
	{
		case AttributeDescriptor::Semantic::position: return 0;
		case AttributeDescriptor::Semantic::normal: return 1;
		case AttributeDescriptor::Semantic::texcoord: return 2;
		default: return -1;
	}
}