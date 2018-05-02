//----------------------------------------------//
//	Author (50%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include <ModelLoader.h>
#include <QFileInfo>
#include <iostream>
#include <AssimpModelLoader.h>
#include <geSG/DefaultImage.h>
#include <geSG/Scene.h>
#include <geSG/Model.h>
#include <QDebug>

using namespace std;
using namespace fsg;
using namespace ge::sg;

void ModelLoader::LoadModel(QString modelFileName, string modelName)
{
	if(loadedModels.count(modelName) != 0)
	{
		// this is OK
		qDebug() << "Model " + QString::fromStdString(modelName) + " was already loaded.";
		return;
	}

	QFileInfo fi(modelFileName);
	string modelPath(qUtf8Printable(fi.canonicalPath() + "/"));

    auto model = AssimpModelLoader::loadScene(modelFileName.toUtf8().constData());
    if(!model)
    {
		// this is not OK
		qDebug() << "Failed to load model " + QString::fromStdString(modelName);
		throw exception("ModelLoader LoadModel - Failed to load model.");    
    }

    LoadImages(model, modelPath);

	loadedModels[modelName] = shared_ptr<Scene>(model);

	qDebug() << "Model " + QString::fromStdString(modelName) + " successfully loaded.";
}

void ModelLoader::LoadImages(Scene* scene, string& imageDir) const
{
	auto defaultImage(make_shared<DefaultImage>());

	for (auto model : scene->models)
	{
		for (auto material : model->materials)
		{
			for (auto it = material->materialComponents.begin(); it != material->materialComponents.end(); ++it)
			{
				if ((*it)->getType() == MaterialComponent::ComponentType::IMAGE)
				{
					auto img = dynamic_cast<MaterialImageComponent*>((*it).get());
					auto textFile(imageDir + img->filePath);
					shared_ptr<QtImage> image(QtImageLoader::loadImage(textFile.c_str()));
					if (image == nullptr)
					{
						img->image = defaultImage;
					}
					else {
						img->image = image;
					}
				}
			}
		}
	}
}

shared_ptr<Scene> ModelLoader::GetModel(string modelName)
{
	if(loadedModels.count(modelName) == 0)
	{
		// this is not OK
		qDebug() << "Tried to get model " + QString::fromStdString(modelName) + " but it wasn't loaded.";
		throw exception("ModelLoader GetModel - Requested model isn't loaded.");
	}

	return loadedModels[modelName];
}

void ModelLoader::UnloadAllModels()
{
	loadedModels.clear();
}
