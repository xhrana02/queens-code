//----------------------------------------------//
//	Author (50%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once

#include <QtImageLoader.h>
#include <QFileInfo>
#include <iostream>
#include <AssimpModelLoader.h>
#include <geSG/DefaultImage.h>
#include <geSG/Scene.h>
#include <geSG/Model.h>

using namespace std;
using namespace ge::sg;

namespace fsg
{
	class ModelLoader
	{
		unordered_map<string, shared_ptr<Scene>> loadedModels;
	public:
		void LoadModel(QString modelFileName, string modelName);
		void LoadImages(Scene* scene, string& imageDir) const;
		shared_ptr<Scene> GetModel(string modelName);
		void UnloadAllModels();
	};
}