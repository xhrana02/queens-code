//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Cursor.h"
#include "RenderingObject.h"

using namespace fsg;
using namespace std;
using namespace glm;

Cursor::Cursor(shared_ptr<RenderingObject> model)
{
    renderingObject = model;
    renderingObject->SetColors(vec4(1.0f,1.0f,1.0f,0.5f), vec4(1.0f,1.0f,1.0f,0.5f), vec4(1.0f,1.0f,1.0f,1.0f));
    renderingObject->Highlight();
    rotationPerFrame = 0.5f; // 30 degrees per second
}

void Cursor::Update(float x, float z, float phase) const
{
    renderingObject->position = vec3(x, 0.05f, z);
    renderingObject->rotation += rotationPerFrame;
    if (renderingObject->rotation > 360.0f)
    {
        renderingObject->rotation -= 360.0f;
    }
    renderingObject->Fluctuate(phase);
}
