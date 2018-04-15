//----------------------------------------------//
//	Author (90%%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>
#include <geSG/Scene.h>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>
#include <geGL/OpenGLContext.h>
#include "GLScene.h"

using namespace std;
using namespace glm;
using namespace ge::gl;
using namespace ge::sg;
using namespace ge::glsg;


namespace fsg
{
	class RenderingObject
	{
		shared_ptr<Scene> model;
		vec3 position;
		vec4 color;

		shared_ptr<Context> glContext;
		shared_ptr<GLScene> glScene;
		unordered_map<Mesh*, shared_ptr<VertexArray>> VAOContainer;
		unordered_map<Mesh*, shared_ptr<Texture>> diffuseTextureContainer;
		bool needToUpdateGLScene = false;
		void updateGLScene();
		static int semantic2Attribute(AttributeDescriptor::Semantic semantic);

	public:
		explicit RenderingObject(Scene* inModel)
			: RenderingObject(inModel, vec3(0,0,0), vec4(1,1,1,1)) {}
		RenderingObject(Scene* inModel, vec3 inPosition)
			: RenderingObject(inModel, inPosition, vec4(1, 1, 1, 1)) {}
		RenderingObject(Scene* inModel, vec4 inColor)
			: RenderingObject(inModel, vec3(0, 0, 0), inColor) {}
		RenderingObject(Scene* inModel, vec3 inPosition, vec4 inColor);

		Scene* GetModel() const
		{
			return model.get();
		}
		void SetModel(Scene* newModel)
		{
			model = make_shared<ge::sg::Scene>(*newModel);
			needToUpdateGLScene = true;
		}

		vec3 GetPosition() const
		{
			return position;
		}
		void SetPosition(vec4 newPosition)
		{
			position = newPosition;
			needToUpdateGLScene = true;
		}

		vec4 GetColor() const
		{
			return color;
		}
		void SetColor(vec4 newColor)
		{
			color = newColor;
			needToUpdateGLScene = true;
		}

		shared_ptr<GLScene> GetGLScene() const
		{
			return glScene;
		}
		shared_ptr<VertexArray> GetVAO(Mesh* mesh)
		{
			return VAOContainer[mesh];
		}
		shared_ptr<Texture> GetDiffuseTexture(Mesh* mesh)
		{
			return diffuseTextureContainer[mesh];
		}

		void PrepareObject(Context* context);

		char* TEST_NAME = "";
	};
}
