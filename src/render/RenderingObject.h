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

namespace fsg
{
	class RenderingObject
	{
		std::shared_ptr<ge::sg::Scene> model;
		glm::vec3 position = glm::vec3(0,0,0);
		glm::vec4 color = glm::vec4(1,1,1,1);
		glm::vec4 normalColor = glm::vec4(1,1,1,1);
		glm::vec4 highlightColor = glm::vec4(1,1,1,1);

		std::shared_ptr<ge::gl::Context> glContext;
		std::shared_ptr<ge::glsg::GLScene> glScene;
		std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::VertexArray>> vaoContainer;
		std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::Texture>> diffuseTextureContainer;
		bool needToUpdateGLScene = false;
		void updateGLScene();
		static int semantic2Attribute(ge::sg::AttributeDescriptor::Semantic semantic);

	public:
		float TextureRepeat = 1;

		explicit RenderingObject(std::shared_ptr<ge::sg::Scene> inModel);

		ge::sg::Scene* GetModel() const
		{
			return model.get();
		}
		void SetModel(std::shared_ptr<ge::sg::Scene> newModel)
		{
			model = newModel;
			needToUpdateGLScene = true;
		}

		glm::vec3 GetPosition() const
		{
			return position;
		}
		void SetPosition(glm::vec3 newPosition)
		{
			position = newPosition;
			needToUpdateGLScene = true;
		}

		glm::vec4 GetColor() const
		{
			return color;
		}
		void SetColor(glm::vec4 newColor)
		{
			normalColor = newColor;
			color = newColor;
		}
		void SetHighlightColor(glm::vec4 newColor)
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


		std::shared_ptr<ge::glsg::GLScene> GetGLScene() const
		{
			return glScene;
		}

		std::shared_ptr<ge::gl::VertexArray> GetVAO(ge::sg::Mesh* mesh)
		{
			return vaoContainer[mesh];
		}

		std::shared_ptr<ge::gl::Texture> GetDiffuseTexture(ge::sg::Mesh* mesh)
		{
			return diffuseTextureContainer[mesh];
		}

		void PrepareObject(std::shared_ptr<ge::gl::Context> context);
	};
}
