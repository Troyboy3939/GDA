#pragma once
#include "MilitaryUnit.h"
class Pikeman :
    public MilitaryUnit
{
public:
    Pikeman();
    Pikeman(Tile* pLocation, Empire* pTeam);
    ~Pikeman();

    void Initialise(Tile* pTile, Empire* pTeam) override;

    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;

    void Upgrade(Icon::IType eUpgrade) override;
private:

    void AttackBuilding(float fDeltaTime)  override;
    void AttackUnit(float fDeltaTime)  override;
};

