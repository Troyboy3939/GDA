#pragma once
#include "GameObject.h"
#include "Floor.h"
#include <vector>
#include "Icon.h"
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


    Unit(Tile* pLocation, Empire* pTeam);
    Unit();

    virtual ~Unit();

    void Update(float fDeltaTime);

    void Draw(aie::Renderer2D* pRenderer);

   virtual void Initialise(Tile* pLocation, Empire* pTeam);


    UType GetUnitType();

    float GetHealth();

    void SetHealth(float fHealth);

    float GetRadius();

    void MoveTo(Vector2 v2Location);

    std::vector<Unit*>& GetGroup();


    virtual void Upgrade(Icon::IType eType) = 0;


    int GetSpeUpgrade();

    Empire* GetTeam();

protected:

    //Movement related functions
    Vector2 Seek(Vector2 v2Locatio);
    Vector2 Arrive(Vector2 v2Location);
    void Separate(Vector2& rv2Force);
    void AlignmentCohesion(Vector2& rv2AForce, Vector2& rv2CentreOfMass);

    std::vector<Unit*> m_apGroup;

    Empire* m_pTeam;


    bool m_bInUse;



    //Movement related

    float m_fMaxSpeed;
    Vector2 m_v2Velocity;
    Vector2 m_v2Steering;
    Vector2 m_v2Destination;
    Path m_av2Path;
    float m_fSkipDistance;
    int m_nPath;
    int m_nSpeUpgrade;
    
    //Unit related variables
    UType m_eUnitType;
    float m_fHealth;
    float m_fRadius;




   
};


