#pragma once
#include "InputComponent.h"


class EcoManager;
class MilitaryManager;
class Blackboard;
class PlansOverseer;


class AIComponent :
    public InputComponent
{
public:
    AIComponent(Empire* pTeam);
    ~AIComponent();


    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;
private:


    EcoManager* m_pEcoManager;
    MilitaryManager* m_pMilitaryManager;


    Blackboard* m_pBlackboard;
    PlansOverseer* m_pPlansOverseer;

};

