#pragma once
#include "Unit.h"


class Building;


class MilitaryUnit :
    public Unit
{
public:

    enum class State
    {
        AttackingUnit,
        AttackingBuilding,
        Idle
    };


    MilitaryUnit();
    MilitaryUnit(Tile* pLocation, Empire* pTeam);
    ~MilitaryUnit();


   virtual void Initialise(Tile* pLocation, Empire* pTeam) override;

   virtual void Update(float fDeltaTime) override;

   virtual void Draw(aie::Renderer2D* pRenderer) override;

   void AttackBuilding(Building* pBuilding);

   void AttackUnit(Unit* pUnit);

   void Idle();

   int GetAttUpgrade();
   int GetDefUpgrade();

   
protected:

    //function that will be called when unit is attacking something
    virtual void AttackBuilding(float fDeltaTime) = 0;

    virtual void AttackUnit(float fDeltaTime) = 0;

    //what the unit is attack (unit or building)
    GameObject* m_pAttacking;

    //what AI state the unit is in
    State m_eState;


    float m_fAttackTimer;

    float m_fAttackCooldown;


    int m_nAttUpgrade;
    int m_nDefUpgrade;


};

