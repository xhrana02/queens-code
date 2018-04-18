//----------------------------------------------//
//	Author (85%): Pavel Hran�� (xhrana02)		//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "RenderingObject.h"
#include "GLSceneProcessor.h"
#include "EnumToGL.h"
#include <geGL/VertexArray.h>

using namespace std;
using namespace fsg;
using namespace ge::gl;
using namespace ge::sg;
using namespace ge::glsg;

RenderingObject::RenderingObject(shared_ptr<Scene> inModel)
{
	model = inModel;
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
					               ge::glsg::translateEnum(glattrib.attributeDescriptor->type), GLsizei(glattrib.attributeDescriptor->stride));
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
				diffuseTextureContainer[meshIt.first] = glScene->textures[imageComponent];
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
		case AttributeDescriptor::Semantic::texcoord: return 2;
		default: return -1;
	}
}
