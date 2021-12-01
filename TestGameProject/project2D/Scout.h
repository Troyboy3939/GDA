#pragma once
#include "MilitaryUnit.h"
class Scout :
    public MilitaryUnit
{
public:
    Scout();
    Scout(Tile* pLocation, Empire* pTeam);
    ~Scout();
    

    void Initialise(Tile* pLocation, Empire* pTeam) override;

    void Update(float fDeltaTime) override;


    void Draw(aie::Renderer2D* pRenderer) override;

    void Upgrade(Icon::IType eUpgrade) override;

private:

  
    void AttackBuilding(float fDeltaTime)  override;
    void AttackUnit(float fDeltaTime)  override;
};

