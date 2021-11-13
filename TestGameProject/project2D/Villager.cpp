#include "Villager.h"
#include "ResourceClass.h"
#include "Empire.h"

Villager::Villager(Vector2 v2Location, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime)
{
	Initialise(v2Location,pTeam,fMaxAmount, fRate, fCycleTime);

}
Villager::Villager() : Unit()
{
	m_fCollectedCount = 0.0f;
	m_fCollectingRate = 0.0f;
	m_fMaximumAmount = 0.0f;
	m_fCycleTime = 0.0f;

	m_fTimer = 0.0f;

	m_pResource = nullptr;

	m_eUnitType = Unit::UType::Villager;

	m_eAIState = State::Idle;
}
Villager::~Villager()
{
}
void Villager::Initialise(Vector2 v2Location, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime)
{
	Unit::Initialise(v2Location,pTeam);

	m_fCollectedCount = 0.0f;
	m_fCollectingRate = fRate;
	m_fMaximumAmount = fMaxAmount;
	m_fCycleTime = fCycleTime;

	m_fTimer = 0.0f;

	m_eUnitType = Unit::UType::Villager;

}
void Villager::AddResource(Resource* pResource)
{
	//If you have space in your inventory
	if (pResource && m_fCollectedCount < m_fMaximumAmount)
	{
		//amount of space in inventory
		auto fSpace = m_fMaximumAmount - m_fCollectedCount;

		//amount of resources left 
		auto fReLeft = pResource->GetResourcesLeft();

		//If the amount left in the inventory is greater than what you can collect per cycle
		if (fSpace > m_fCollectingRate && pResource->GetResourcesLeft() >= m_fCollectingRate)
		{
			//Add the total amount that you can grab into your inventory
			m_fCollectedCount += m_fCollectingRate;

			//Add amount to inventory
			m_Inventory[static_cast<int>(pResource->GetType())] += m_fCollectingRate;

			return;
		} //the amount left is less than what you can grab every second
		else if(fSpace <= m_fCollectingRate && pResource->GetResourcesLeft() >= fSpace)
		{

			//Add the total amount that you can grab into your inventory
			m_fCollectedCount += fSpace;

			//Add amount to inventory
			m_Inventory[static_cast<int>(pResource->GetType())] += fSpace;
			return;

		} //if there is space for the amount left and 
		else if (fSpace >= fReLeft && fReLeft > 0 && fReLeft <= m_fCollectingRate)
		{
			//Add the total amount that you can grab into your inventory
			m_fCollectedCount += fReLeft;

			//Add amount to inventory
			m_Inventory[static_cast<int>(pResource->GetType())] += fReLeft;
			return;
		}

	}

}

void Villager::Update(float fDeltaTime)
{

	switch (m_eAIState)
	{
	case Villager::State::MiningGold:
		break;
	case Villager::State::CuttingWood:
		break;
	case Villager::State::PickingBerries:
		break;
	case Villager::State::Building:
		break;
	case Villager::State::Idle:
		break;
	default:
		break;
	}



}

void Villager::Draw(aie::Renderer2D* pRenderer)
{
	if (pRenderer)
	{
		auto v3Colour = m_pTeam->GetTeamColour();

		pRenderer->setRenderColour(v3Colour.x,v3Colour.y,v3Colour.z);

		//Draw villager
		pRenderer->drawCircle(m_v2Position.x, m_v2Position.y, 10.0f,0.0f);
		pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	}
}
