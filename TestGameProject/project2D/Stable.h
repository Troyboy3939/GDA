#pragma once
#include "Building.h"

class Stable :
    public Building
{
public:
    Stable(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);
    Stable();
    ~Stable();


    void Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);



    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer);

    float GetProgress() override;

private:
    float m_fTimer;
    float m_fUpgradeTime;
    float m_fUnitTime;


};

