#pragma once
#include "MilitaryUnit.h"
class Archer :
    public MilitaryUnit
{
public:
    Archer();
    Archer(Tile* pLocation, Empire* pTeam);
    ~Archer();

    void Initialise(Tile* pTile, Empire* pTeam) override;

    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;

    void Upgrade(Icon::IType eUpgrade) override;
private:

    void AttackBuilding(float fDeltaTime)  override;
    void AttackUnit(float fDeltaTime)  override;



    float m_fAttackLerp;
    float m_fArrowSpeed;
    float m_fDisToTarg;

};

