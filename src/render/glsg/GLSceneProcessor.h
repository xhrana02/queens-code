//----------------------------------------------//
//	Modified by (5%): Pavel Hranáè (xhrana02)	//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <memory>

namespace ge
{
   namespace gl{
      class Texture;
      class Context;
   }

   namespace sg
   {
      class MaterialImageComponent;
      class Scene;
      class Mesh;
   }

   namespace glsg
   {
      class GLScene;
   }
}

namespace ge
{
	namespace glsg
	{
		/**
		* Base class for texture factory.
		*/
		class TextureFactory
		{
		public:
			virtual ~TextureFactory() = default;
			/**
			* This function is called with active OpenGL context when the GLSceneProcessor processes
			* MaterialImageComponent.
			*/
			virtual std::shared_ptr<gl::Texture> create(sg::MaterialImageComponent* img, std::shared_ptr<gl::Context>& context) = 0;
		};

		/**
		* Used when no custom factory is provided by user. It will generate RGBA8 texture with mipmaps and set min filter to
		* GL_LINEAR_MIPMAP_LINEAR and mag filter to GL_LINEAR
		*/
		class DefaultTextureFactory : public TextureFactory
		{
			std::shared_ptr<gl::Texture> create(sg::MaterialImageComponent* img, std::shared_ptr<gl::Context>& context) override;
		};

		/**
		* Class that creates and initializes the GLScene class. It creates gl::Buffer for every AttributeDescriptor
		* And Texture for every MaterialImageComponent. OpenGL context needs to be <b>active</b> before you
		* call process(). You can also supply a custom TextureFactory object to supervise texture and sampler
		* creation.
		*/
		class GLSceneProcessor
		{
		public:
			explicit GLSceneProcessor(std::shared_ptr<gl::Context> context = nullptr);

			static std::shared_ptr<glsg::GLScene> processScene(std::shared_ptr<sg::Scene> scene, std::shared_ptr<gl::Context> context, std::shared_ptr<TextureFactory> textureFactory = std::shared_ptr<DefaultTextureFactory>(std::make_shared<DefaultTextureFactory>()));


			std::shared_ptr<TextureFactory> textureFactory;

		private:
			static void processMeshes(std::shared_ptr<sg::Scene>& scene, std::shared_ptr<glsg::GLScene>& glscene, std::shared_ptr<gl::Context> context);
			//static void createGLAttribs(sg::Mesh* mesh, std::shared_ptr<glsg::GLScene>& glscene);
			static void createTextures(std::shared_ptr<sg::Scene> scene, std::shared_ptr<GLScene> glscene, std::shared_ptr<gl::Context> context, std::shared_ptr<TextureFactory> textureFactory);
		};
	}

}