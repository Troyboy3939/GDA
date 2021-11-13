#include "BuildingPool.h"
#include "TownCentre.h"


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
		break;
	case Building::BType::Barracks:
		break;
	case Building::BType::ArcheryRange:
		break;
	case Building::BType::Stable:
		break;
	case Building::BType::NoTypes:
	default:
		return nullptr;
	}

	return nullptr;
}
