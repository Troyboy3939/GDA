#pragma once
#include "Building.h"
class TownCentre :
    public Building
{
public:

    TownCentre(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);

    TownCentre();
    ~TownCentre();


    void Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);

    

    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer);

    float GetProgress() override;


private:

    float m_fVillagerTime;
    float m_fUpgradeTime;
    float m_fAgeUpTime;

    float m_fTimer;


};

