#pragma once
#include "GameObject.h"
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

    Building(aie::Texture* pTexture, Vector2 v2Location);
    Building();

    virtual ~Building() = 0;

    void Initialise(aie::Texture* pTexture, Vector2 v2Location);

    BType GetBuildingType();

protected:
    aie::Texture* m_pTexture;
    

    BType m_eBuildingType;
};

