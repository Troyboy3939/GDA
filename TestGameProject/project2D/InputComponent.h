#pragma once
#include "Renderer2D.h"
class Empire;

class InputComponent
{
public:
	InputComponent(Empire* pTeam);

	Empire* GetTeam();


	virtual void Update(float fDeltaTime) = 0;

	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

protected:
	Empire* m_pTeam;

};

