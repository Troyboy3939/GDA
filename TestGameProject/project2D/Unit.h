#pragma once
#include "GameObject.h"

#include "Floor.h"
class Empire;


class Unit :
    public GameObject
{
public:
    enum class UType
    {
        Villager,
        Knight,
        Scout,
        Skirmisher,
        Archer,
        Swordsman,
        Pikeman,
        NoUnitTypes
    };


    Unit(Vector2 v2Location, Empire* pTeam);
    Unit();
    virtual ~Unit();

    void Update(float fDeltaTime);

    void Draw(aie::Renderer2D* pRenderer);

    void Initialise(Vector2 v2Location, Empire* pTeam);


    UType GetUnitType();

    float GetHealth();

    void SetHealth(float fHealth);

protected:
    Empire* m_pTeam;

    //Get a path from Empire
    Path m_av2Path;

    UType m_eUnitType;

    float m_fHealth;

};

