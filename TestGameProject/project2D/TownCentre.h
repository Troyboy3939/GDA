#pragma once
#include "Building.h"
class TownCentre :
    public Building
{
public:

    TownCentre(aie::Texture* pTexture, Vector2 v2Location);

    TownCentre();
    ~TownCentre();

    

    void Update(float fDeltaTime);

    void Draw(aie::Renderer2D* pRenderer);

};

