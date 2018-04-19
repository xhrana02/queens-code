//----------------------------------------------//
//	Author (50%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QtImageLoader.h>
#include <AssimpModelLoader.h>
#include <geSG/Scene.h>

namespace fsg
{
	class ModelLoader
	{
		std::unordered_map<std::string, std::shared_ptr<ge::sg::Scene>> loadedModels;
	public:
		void LoadModel(QString modelFileName, std::string modelName);
		void LoadImages(ge::sg::Scene* scene, std::string& imageDir) const;
		std::shared_ptr<ge::sg::Scene> GetModel(std::string modelName);
		void UnloadAllModels();
	};
}