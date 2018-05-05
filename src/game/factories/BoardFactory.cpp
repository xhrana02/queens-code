//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "BoardFactory.h"
#include "IceBlock.h"
#include "Player.h"

using namespace fsg;
using namespace std;
using namespace glm;

void BoardFactory::PopulateNewBoard(Board* newBoard, fsg::ModelLoader* modelLoader)
{
    modelLoader->LoadModel(APP_RESOURCES"/models/FieldBorder/FieldBorder.obj", "FieldBorder");
    modelLoader->LoadModel(APP_RESOURCES"/models/IceBlock/IceBlock.obj", "IceBlock");

    for (auto x = 1; x <= newBoard->PlayableWidth(); x++)
    {
        for (auto y = 1; y <= newBoard->PlayableHeight(); y++)
        {
            auto field = newBoard->GetField(x, y);

            auto newBorderObject = make_shared<RenderingObject>(modelLoader->GetModel("FieldBorder"));
            newBorderObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
            newBorderObject->SetColors(BORDER_NORMAL_COLOR, BORDER_HALFLIGHT_COLOR, BORDER_HIGHLIGHT_COLOR);
            field->SetFieldBorderObject(newBorderObject);

            auto newIceBlockObject = make_shared<RenderingObject>(modelLoader->GetModel("IceBlock"));
            newIceBlockObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
            newIceBlockObject->SetColors(ICE_BLOCK_NORMAL_COLOR, ICE_BLOCK_HALFLIGHT_COLOR, ICE_BLOCK_HIGHLIGHT_COLOR);
            field->SetFieldIceBlockObject(newIceBlockObject);

            auto newIceBlockUnit = make_shared<IceBlock>();
            field->SetFieldIceBlockUnit(newIceBlockUnit);
        }
    }
}

shared_ptr<Board> BoardFactory::CreateStandardBoard(ModelLoader* modelLoader)
{
    auto newBoard = make_shared<Board>(15, 15);

    modelLoader->LoadModel(APP_RESOURCES"/models/Throne/Throne.obj", "Throne");
    modelLoader->LoadModel(APP_RESOURCES"/models/StoneWall/StoneWall.obj", "StoneWall");

    auto throneObject = make_shared<RenderingObject>(modelLoader->GetModel("Throne"));
    throneObject->TextureRepeat = 10;
    newBoard->GetField(8, 8)->SetFieldTerrainObject(throneObject);
    newBoard->GetField(8, 8)->SetTerrainType(Throne);

    vector<Field*> wallFields;
    // bottom left corner
    wallFields.push_back(newBoard->GetField(5, 5));
    wallFields.push_back(newBoard->GetField(5, 6));
    wallFields.push_back(newBoard->GetField(6, 5));
    // top left corner
    wallFields.push_back(newBoard->GetField(5, 10));
    wallFields.push_back(newBoard->GetField(5, 11));
    wallFields.push_back(newBoard->GetField(6, 11));
    // bottom right corner
    wallFields.push_back(newBoard->GetField(10, 5));
    wallFields.push_back(newBoard->GetField(11, 5));
    wallFields.push_back(newBoard->GetField(11, 6));
    // top right corner
    wallFields.push_back(newBoard->GetField(10, 11));
    wallFields.push_back(newBoard->GetField(11, 10));
    wallFields.push_back(newBoard->GetField(11, 11));

    for (auto field : wallFields)
    {
        auto newWallObject = make_shared<RenderingObject>(modelLoader->GetModel("StoneWall"));
        newWallObject->position = vec3(field->GetRenderingPosX(), 0.0f, field->GetRenderingPosZ());
        field->SetFieldTerrainObject(newWallObject);
        field->SetTerrainType(Wall);
    }

    PopulateNewBoard(newBoard.get(), modelLoader);

    return newBoard;
}

shared_ptr<Board> BoardFactory::CreateTrainingDuelBoard(ModelLoader* modelLoader)
{
    auto newBoard = make_shared<Board>(5, 12);

    PopulateNewBoard(newBoard.get(), modelLoader);

    return newBoard;
}

shared_ptr<Board> BoardFactory::CreateChessBoard(ModelLoader* modelLoader)
{
    auto newBoard = make_shared<Board>(8, 8);

    PopulateNewBoard(newBoard.get(), modelLoader);

    return newBoard;
}
