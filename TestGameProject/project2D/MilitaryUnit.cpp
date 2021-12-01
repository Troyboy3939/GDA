#include "MilitaryUnit.h"
#include "Empire.h"
MilitaryUnit::MilitaryUnit() : Unit()
{

	m_eState = State::Idle;

	m_nAttUpgrade = 0;
	m_nDefUpgrade = 0;
	m_nSpeUpgrade = 0;
}

MilitaryUnit::MilitaryUnit(Tile* pLocation, Empire* pTeam)
{
	Initialise(pLocation, pTeam);
}

MilitaryUnit::~MilitaryUnit()
{
}

void MilitaryUnit::Initialise(Tile* pLocation, Empire* pTeam)
{
	Unit::Initialise(pLocation, pTeam);

	m_eState = State::Idle;
	m_nAttUpgrade = 0;
	m_nDefUpgrade = 0;
	m_nSpeUpgrade = 0;

}

void MilitaryUnit::Update(float fDeltaTime)
{
	//Add pathfinding steering to the steering then move in the appropriate direction
	Unit::Update(fDeltaTime);


	switch (m_eState)
	{
	case MilitaryUnit::State::AttackingUnit:
		AttackUnit(fDeltaTime);
		break;
	case MilitaryUnit::State::AttackingBuilding:
		AttackBuilding(fDeltaTime);
		break;
	case MilitaryUnit::State::Idle:
	default:
		break;
	}

}

void MilitaryUnit::Draw(aie::Renderer2D* pRenderer)
{
	Unit::Draw(pRenderer);

}

void MilitaryUnit::AttackBuilding(Building* pBuilding)
{
	m_eState = State::AttackingBuilding;

	m_pAttacking = pBuilding;
}

void MilitaryUnit::AttackUnit(Unit* pUnit)
{
	m_eState = State::AttackingUnit;

	m_pAttacking = pUnit;

	if (m_pAttacking == this)
	{
		m_pAttacking = nullptr;
	}
}

void MilitaryUnit::Idle()
{
	m_eState = State::Idle;
}

int MilitaryUnit::GetAttUpgrade()
{
	return m_nAttUpgrade;
}

int MilitaryUnit::GetDefUpgrade()
{
	return m_nDefUpgrade;
}

