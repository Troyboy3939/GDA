#pragma once
#include "GameObject.h"
#include <vector>
#include "Vector3.h"
#include "Icon.h"

class Floor;
class Tile;
class Empire;

class Building :
    public GameObject
{
public:

    enum class BType
    {
        TownCentre,
        Storage,
        Barracks,
        ArcheryRange,
        Stable,
        NoTypes
    };

    Building(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);
    Building();

    virtual ~Building() = 0;

    virtual void Update(float fDeltaTime);

    virtual void Draw(aie::Renderer2D* pRenderer);

    void Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost);

    BType GetBuildingType();

    Icons& GetIcons();

    float GetPercentageComplete();

    void SetPercentageComplete(float fPercentage);

    Tile* GetTile();

    virtual float GetProgress() = 0;

    Icon* GetCurrentAction();

    void AddActionToQueue(Icon* pIcon);

    int GetActionsLeft();

    float GetGold();
    float GetWood();
    float GetFood();

    void SetFood(float fFood);
    void SetWood(float fWood);
    void SetGold(float fGold);

    Empire* GetTeam();

    float GetHealth();
    void SetHealth(float fHealth);

    
protected:
    float m_fPercentageComplete;

    void TurnTilesOff();

    Icons m_aActionQueue;

    aie::Texture* m_pTexture;
    Floor* m_pFloor;

    Tile* m_pBottomLeft;

    BType m_eBuildingType;

    Icons m_apIcons;

    Empire* m_pTeam;


    float m_fWood;
    float m_fFood;
    float m_fGold;

    float m_fHealth;

   
};

