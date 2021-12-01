#pragma once
#include "Building.h"

class ArcheryRange :
    public Building
{
public:
    ArcheryRange(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);
    ArcheryRange();
    ~ArcheryRange();


    void Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);



    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer);

    float GetProgress() override;

private:

    float m_fTimer;

    float m_fUnitTime;
    float m_fUpgradeTime;

};

