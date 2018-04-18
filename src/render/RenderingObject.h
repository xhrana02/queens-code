//----------------------------------------------//
//	Author (85%): Pavel Hranáè (xhrana02)		//
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
		vec3 position = vec3(0,0,0);
		vec4 color = vec4(1,1,1,1);
		vec4 normalColor = vec4(1,1,1,1);
		vec4 highlightColor = vec4(1,1,1,1);

		shared_ptr<Context> glContext;
		shared_ptr<GLScene> glScene;
		unordered_map<Mesh*, shared_ptr<VertexArray>> vaoContainer;
		unordered_map<Mesh*, shared_ptr<Texture>> diffuseTextureContainer;
		bool needToUpdateGLScene = false;
		void updateGLScene();
		static int semantic2Attribute(AttributeDescriptor::Semantic semantic);

	public:
		float TextureRepeat = 1;

		explicit RenderingObject(shared_ptr<Scene> inModel);

		Scene* GetModel() const
		{
			return model.get();
		}
		void SetModel(shared_ptr<Scene> newModel)
		{
			model = newModel;
			needToUpdateGLScene = true;
		}

		vec3 GetPosition() const
		{
			return position;
		}
		void SetPosition(vec3 newPosition)
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
			normalColor = newColor;
			color = newColor;
		}
		void SetHighlightColor(vec4 newColor)
		{
			highlightColor = newColor;
		}
		void Highlight()
		{
			color = highlightColor;
		}
		void Unhighlight()
		{
			color = normalColor;
		}


		shared_ptr<GLScene> GetGLScene() const
		{
			return glScene;
		}
		shared_ptr<VertexArray> GetVAO(Mesh* mesh)
		{
			return vaoContainer[mesh];
		}
		shared_ptr<Texture> GetDiffuseTexture(Mesh* mesh)
		{
			return diffuseTextureContainer[mesh];
		}

		void PrepareObject(shared_ptr<Context> context);
	};
}
