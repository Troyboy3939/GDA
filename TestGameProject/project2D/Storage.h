#pragma once
#include "Building.h"

class Empire;

class Storage :
    public Building
{
public:
    Storage(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);
    Storage();


    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;

    void Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);

    virtual float GetProgress() override;

};

