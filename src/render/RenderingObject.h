//----------------------------------------------//
//	Author (85%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>
#include <geSG/Scene.h>
#include <glm/glm.hpp>
#include <geGL/OpenGLContext.h>
#include "GLScene.h"

namespace fsg
{
	class RenderingObject
	{
		std::shared_ptr<ge::sg::Scene> model;
		glm::vec4 color = glm::vec4(1,1,1,1);
		glm::vec4 normalColor = glm::vec4(1,1,1,1);
		glm::vec4 highlightColor = glm::vec4(1,1,1,1);

		std::shared_ptr<ge::gl::Context> glContext;
		std::shared_ptr<ge::glsg::GLScene> glScene;
		std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::VertexArray>> vaoContainer;
		std::unordered_map<ge::sg::Mesh*, std::shared_ptr<ge::gl::Texture>> textureContainer;
		bool needToUpdateGLScene = false;
		void updateGLScene();
		static int semantic2Attribute(ge::sg::AttributeDescriptor::Semantic semantic);

	public:
		glm::vec3 position = glm::vec3(0,0,0);
		float rotation = 0;
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

		glm::vec4 GetColor() const
		{
			return color;
		}
		glm::vec4 GetNormalColor() const
		{
			return normalColor;
		}
		glm::vec4 GetHighlightColor() const
		{
			return highlightColor;
		}
		void SetColors(glm::vec4 normal, glm::vec4 highlight)
		{
			normalColor = normal;
			highlightColor = highlight;
			color = normalColor;
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

		std::shared_ptr<ge::gl::Texture> GetTexture(ge::sg::Mesh* mesh)
		{
			return textureContainer[mesh];
		}

		void PrepareObject(std::shared_ptr<ge::gl::Context> context);
	};
}
