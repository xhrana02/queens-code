//----------------------------------------------//
//	Author (50%): Pavel Hranáè (xhrana02)		//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include <ModelLoader.h>

using namespace std;
using namespace fsg;

void ModelLoader::LoadModel(QString modelFileName, string modelName)
{
    QFileInfo fi(modelFileName);
    string modelPath(qUtf8Printable(fi.canonicalPath() + "/"));
	if(loadedModels.count(modelName) != 0)
	{
		cerr << "Model " << modelName << " was already loaded" << endl;
	}

    auto model = AssimpModelLoader::loadScene(modelFileName.toUtf8().constData());
    if(!model)
    {
        cerr << "Failed to load model" << modelName << endl;      
    }

    LoadImages(model, modelPath);

	loadedModels[modelName] = shared_ptr<Scene>(model);
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
		throw exception("Requested model isn't loaded.");
	}

	return loadedModels[modelName];
}

void ModelLoader::UnloadAllModels()
{
	loadedModels.clear();
}
