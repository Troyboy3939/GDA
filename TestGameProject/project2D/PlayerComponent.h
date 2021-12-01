#pragma once
#include "InputComponent.h"
#include "Vector2.h"
#include "Input.h"


class Icon;

class Unit;
class Building;
class UI;

using Units = std::vector<Unit*>;


class PlayerComponent :
    public InputComponent
{
public:
    PlayerComponent(Empire* pTeam);
    ~PlayerComponent();



    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;


    Units& GetSelectedUnits();

    Building* GetSelectedBuilding();

private:
    void PlaceBuilding(int nBuildingType);


    void VillagerRightClick(Vector2 v2Location);
    void MilitaryRightClick(Vector2 v2Location);

    void UpdateInputs(float fDeltaTime);
    void UpdateCamera(aie::Renderer2D* pRenderer);


    Vector2 m_v2Mouse;
    Vector2 m_v2PressedLocation;
    Vector2 m_v2ReleasedLocation;
    Vector2 m_v2CameraPos;

    float m_fDeltaTime;
    float m_fHoldTimer;

    bool m_bMousePressed;
    bool m_bMouseReleased;
    bool m_bPlaced;

    aie::Input* m_pInput;


    Units m_apSelectedUnits;
    Building* m_pSelectedBuilding;
    Icon* m_pIcon;

    UI* m_pUI;

    float m_fCameraSpeed;

};

