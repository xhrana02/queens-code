//----------------------------------------------//
//	Modified by (0%): Pavel Hran�� (xhrana02)	//
//	School: Vysok� u�en� technick� v Brn�		//
//	Faculty: Fakulta informa�n�ch technologi�	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <glsg/GLAttribute.h>
#include <glm/detail/type_vec3.hpp>


namespace ge
{
	namespace gl{
		class Texture;
	}

	namespace sg
	{
		class MaterialImageComponent;
		class Scene;
		class Model;
		class Mesh;
	}

	namespace glsg
	{
		/**
		* Maps geSG Scene Meshes and Images to geGL provided structures.
		* This class provides the link between implementation independent scene graph
		* and OpenGL.
		* Meshes are mapped to a collection of GLAttributes and MaterialImageComponents
		* are mapped to ge::gl::TextureObjects
		* This class is just a data conatiner. Management needs to be provided elsewhere.
		*/
		class GLScene
		{
		public:
			typedef std::vector<GLAttribute> GLAttribArray;

			GLScene() : scene(nullptr){}

			std::shared_ptr<ge::sg::Scene> scene; ///< The original scene
			std::unordered_map<ge::sg::Mesh*, GLAttribArray> GLMeshes; ///< Dictionary connecting mesh with its GLAttribArray
			std::unordered_map<ge::sg::MaterialImageComponent*, std::shared_ptr<gl::Texture>> textures; ///< Dictionary connecting MaterialImageComponent with Texture
		};
	}
}
