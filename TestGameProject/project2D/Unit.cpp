#include "Unit.h"

Unit::Unit(Vector2 v2Location, Empire* pTeam)
{
	Initialise(v2Location,pTeam);
}

Unit::Unit() : GameObject()
{
	m_pTeam = nullptr;
}


Unit::~Unit()
{
}

void Unit::Update(float fDeltaTime)
{
}

void Unit::Draw(aie::Renderer2D* pRenderer)
{
}

void Unit::Initialise(Vector2 v2Location, Empire* pTeam)
{
	
	GameObject::Initialise(v2Location);

	m_pTeam = pTeam;
}

Unit::UType Unit::GetUnitType()
{
	return m_eUnitType;
}

float Unit::GetHealth()
{
	return m_fHealth;
}

void Unit::SetHealth(float fHealth)
{
	m_fHealth = fHealth;
}
