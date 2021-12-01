#include "UnitPool.h"
#include "Villager.h"
#include "Swordsman.h"
#include "Pikeman.h"
#include "Knight.h"
#include "Scout.h"
#include "Archer.h"
#include "Skirmisher.h"

UnitPool::UnitPool(int nAmountPerUnit)
{
	//Reserve enough for each unit
	//m_apPool.reserve(static_cast<int>(Unit::UType::NoUnitTypes) * nAmountPerUnit);

	//Reserve enough for Villager DELETE THIS LATER, USE ABOVE LINE
	m_apPool.reserve(nAmountPerUnit);

	//Create units
	for (int i = 0; i < nAmountPerUnit; i++)
	{
		m_apPool.push_back(new Villager());
		m_apPool.push_back(new Swordsman());
		m_apPool.push_back(new Pikeman());
		m_apPool.push_back(new Archer());
		m_apPool.push_back(new Skirmisher());
		m_apPool.push_back(new Scout());
		m_apPool.push_back(new Knight());
	}



}

UnitPool::~UnitPool()
{
	for (int i = 0; i < m_apPool.size(); i++)
	{
		delete m_apPool[i];
	}

}

Unit* UnitPool::GetUnit(Unit::UType eType)
{

	if (eType != Unit::UType::NoUnitTypes)
	{
		for (int i = 0; i < m_apPool.size(); i++)
		{
			if (m_apPool[i])
			{
				//if this hasn't been used and is the correct type
				if (!m_aInUse[m_apPool[i]] && m_apPool[i]->GetUnitType() == eType)
				{
					//set to being used
					m_aInUse.insert_or_assign(m_apPool[i],true);

					return m_apPool[i];
				}
			}
		}


		//If code reaches here than there are no more units left, so create another one
		auto pUnit = CreateUnit(eType);

		m_aInUse.insert_or_assign(pUnit, true);

		return pUnit;


	}

	return nullptr;
}




void UnitPool::Return(Unit* pUnit)
{
	m_aInUse.insert_or_assign(pUnit,false);
}

std::vector<Unit*>& UnitPool::GetPool()
{
	return m_apPool;
}

Unit* UnitPool::GetUnitAtLocation(Vector2 v2Location)
{

	for (auto pUnit : m_apPool)
	{
		if (pUnit && m_aInUse[pUnit])
		{
			auto v2ToUnit = pUnit->GetPosition() - v2Location;

			auto fRadius = pUnit->GetRadius();


			if (v2ToUnit.magnitudeSq() < fRadius * fRadius)
			{
				return pUnit;
			}
		}
	}



	return nullptr;
}

Unit* UnitPool::GetClosestUnit(Unit* pUnit, float fRadius, Empire* pExclusion)
{

	auto fClosest = -1.0f;

	Unit* pClosest = nullptr;

	if (pUnit)
	{

		for (auto pNearby : m_apPool)
		{

			//exists, in use and not on the same team as pExclusion
			if (pNearby && m_aInUse[pNearby] && pNearby->GetTeam() != pExclusion && pNearby != pUnit)
			{
				auto v2Dis = pNearby->GetPosition() - pUnit->GetPosition();
				auto fMagSq = v2Dis.magnitudeSq();

				if (fClosest < 0.0f && fMagSq < fRadius * fRadius)
				{
					fClosest = fMagSq;
					pClosest = pNearby;
				}
				else if (fMagSq < fClosest && fMagSq < fRadius * fRadius)
				{
					fClosest = v2Dis.magnitudeSq();
					pClosest = pNearby;
				}
			}
		}
	}



	return pClosest;
}

Unit* UnitPool::CreateUnit(Unit::UType eType)
{
	switch (eType)
	{
	case Unit::UType::Villager:
	{
		auto pVill = new Villager();

		m_apPool.push_back(pVill);
		return pVill;
		break;
	}
	case Unit::UType::Knight:
	{
		auto pKnight = new Knight();

		m_apPool.push_back(pKnight);
		return pKnight;
		break;
	}
		break;
	case Unit::UType::Scout:
	{
		auto pScout = new Scout();

		m_apPool.push_back(pScout);
		return pScout;
		break;
	}
		break;
	case Unit::UType::Skirmisher:
	{
		auto pSkirmisher = new Skirmisher();

		m_apPool.push_back(pSkirmisher);
		return pSkirmisher;
		break;
	}
		break;
	case Unit::UType::Archer:
	{
		auto pArcher = new Archer();

		m_apPool.push_back(pArcher);
		return pArcher;
		break;
	}
		break;
	case Unit::UType::Swordsman:
	{
		auto pSwordsman = new Swordsman();

		m_apPool.push_back(pSwordsman);
		return pSwordsman;
	}
		break;
	case Unit::UType::Pikeman:
	{
		auto pPikeman = new Pikeman();

		m_apPool.push_back(pPikeman);
		return pPikeman;
	}
		break;
	case Unit::UType::NoUnitTypes:
	default:
		return nullptr;
		break;
	}
	return nullptr;
}
