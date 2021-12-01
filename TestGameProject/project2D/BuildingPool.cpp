#include "BuildingPool.h"
#include "TownCentre.h"
#include "Storage.h"
#include "Barracks.h"
#include "Stable.h"
#include "ArcheryRange.h"
BuildingPool::BuildingPool(int nDefaultAmount)
{
	//Reserve enough for each unit
	//m_apPool.reserve(static_cast<int>(Unit::UType::NoUnitTypes) * nAmountPerUnit);

	//Reserve enough for Villager DELETE THIS LATER, USE ABOVE LINE
	m_apPool.reserve(nDefaultAmount);

	//Create units
	for (int i = 0; i < nDefaultAmount; i++)
	{
		m_apPool.push_back(new TownCentre());
		m_apPool.push_back(new Storage());
		m_apPool.push_back(new Barracks());
		m_apPool.push_back(new Stable());
		m_apPool.push_back(new ArcheryRange());
	}



}

BuildingPool::~BuildingPool()
{
	for (int i = 0; i < m_apPool.size(); i++)
	{
		delete m_apPool[i];
	}

}

Building* BuildingPool::GetBuilding(Building::BType eType)
{

	if (eType != Building::BType::NoTypes)
	{
		for (int i = 0; i < m_apPool.size(); i++)
		{
			if (m_apPool[i])
			{
				//if this hasn't been used and is the correct type
				if (!m_aInUse[m_apPool[i]] && m_apPool[i]->GetBuildingType() == eType)
				{
					//set to being used
					m_aInUse.insert_or_assign(m_apPool[i], true);

					return m_apPool[i];
				}
			}
		}

		//if code reaches here than there are none left so create another

		auto pBuilding = CreateBuilding(eType);

		m_aInUse.insert_or_assign(pBuilding, true);

		return pBuilding;


	}

	return nullptr;
}

void BuildingPool::Return(Building* pBuilding)
{
	m_aInUse.insert_or_assign(pBuilding, false);

}

Building* BuildingPool::GetBuildingAtLocation(Vector2 v2Location)
{
	

	for (auto pBuilding : m_apPool)
	{
		if (pBuilding && m_aInUse[pBuilding])
		{
			auto v2BuildPos = pBuilding->GetPosition();


			if (v2Location.x > v2BuildPos.x - 64 && v2Location.x < v2BuildPos.x + 64)
			{
				if (v2Location.y > v2BuildPos.y - 64 && v2Location.y < v2BuildPos.y + 64)
				{
					return pBuilding;
				}

			}
		}
	}



	return nullptr;
}

Building* BuildingPool::GetClosestBuilding(Building* pBuilding, float fRadius, Empire* pExclusion)
{
	auto fClosest = -1.0f;

	Building* pClosest = nullptr;

	if (pBuilding)
	{

		for (auto pNearby : m_apPool)
		{

			//exists, in use and not on the same team as pExclusion
			if (pNearby && m_aInUse[pNearby] && pNearby->GetTeam() != pExclusion && pNearby != pBuilding)
			{
				auto v2Dis = pNearby->GetPosition() - pBuilding->GetPosition();
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

Building* BuildingPool::CreateBuilding(Building::BType eType)
{
	switch (eType)
	{
	case Building::BType::TownCentre:
	{
		auto pTC = new TownCentre();
		m_apPool.push_back(pTC);

		return pTC;
		break;
	}
	case Building::BType::Storage:
	{
		auto pStorage = new Storage();
		m_apPool.push_back(pStorage);

		return pStorage;

		break;
	}
	case Building::BType::Barracks:
	{

		break;
	}
	case Building::BType::ArcheryRange:
	{

		break;
	}
	case Building::BType::Stable:
	{

		break;
	}
	case Building::BType::NoTypes:
	default:
		return nullptr;
	}

	return nullptr;
}
