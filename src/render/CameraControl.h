//----------------------------------------------//
//  Author: Pavel Hran�� (xhrana02)             //
//  School: Vysok� u�en� technick� v Brn�       //
//  Faculty: Fakulta informa�n�ch technologi�   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Camera.h"

namespace fsg
{
    class Simple_geSGRenderer;

    class CameraControl
    {
        Camera* camera = nullptr;

        float positionX = 0;
        float positionXMin;
        float positionXMax;
        float const positionY = 0.5;
        float positionZ = 0;
        float positionZMin;
        float positionZMax;

        float rotationX = 270;
        float rotationY = 50;
        float const rotationYMin = 15;
        float const rotationYMax = 85;

        float distance = 5;
        float const distanceMin = 2;
        float const distanceMax = 12;

    public:
        explicit CameraControl(Camera* inCamera, int mapSize);
        void Pan(float x, float z);
        void PanToPosition(float x, float z);
        void Rotate(float x, float y);
        void Zoom(float zoomChange);
        void CheckPositionBounds();
        void CheckRotationBounds();
        void CheckDistanceBounds();
        void UpdateCamera() const;
        glm::vec2 CalculateMousePosition(float x, float y, Simple_geSGRenderer* renderer) const;
    };
}

