#pragma once
#include "InputComponent.h"
class AIComponent :
    public InputComponent
{
public:
    AIComponent(Empire* pTeam);


    void Update(float fDeltaTime) override;

    void Draw(aie::Renderer2D* pRenderer) override;
private:

};

