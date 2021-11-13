#include "UnitPool.h"
#include "Villager.h"
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
		break;
	case Unit::UType::Scout:
		break;
	case Unit::UType::Skirmisher:
		break;
	case Unit::UType::Archer:
		break;
	case Unit::UType::Swordsman:
		break;
	case Unit::UType::Pikeman:
		break;
	case Unit::UType::NoUnitTypes:
	default:
		return nullptr;
		break;
	}
	return nullptr;
}
