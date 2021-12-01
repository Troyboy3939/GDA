#include "Villager.h"
#include "ResourceClass.h"
#include "Empire.h"
#include "Storage.h"
#include "Icon.h"

Villager::Villager(Tile* pLocation, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime)
{
	Initialise(pLocation,pTeam,fMaxAmount, fRate, fCycleTime);

}
Villager::Villager() : Unit()
{
	m_fCollectedCount = 0.0f;
	m_fCollectingRate = 0.0f;
	m_fMaximumAmount = 0.0f;
	m_fCycleTime = 0.0f;

	m_fMiningTimer = -1.0f;

	m_pResource = nullptr;

	m_eUnitType = Unit::UType::Villager;

	m_eAIState = State::Idle;

	m_fCloseDistance = 85.0f;

	m_fBuildPercentPerSec = 3.33333f;

	m_pBuilding = nullptr;

	m_pStorage = nullptr;

	m_pFloor = nullptr;

	m_pResource = nullptr;

	m_nInventoryUpgrade = 0;



}
Villager::~Villager()
{
}
void Villager::Initialise(Tile* pLocation, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime)
{
	Unit::Initialise(pLocation,pTeam);

	m_fCollectedCount = 0.0f;
	m_fCollectingRate = fRate;
	m_fMaximumAmount = fMaxAmount;
	m_fCycleTime = fCycleTime;

	m_fMiningTimer = 0.0f;

	m_eUnitType = Unit::UType::Villager;

	m_pFloor = m_pTeam->GetFloor();


	m_fCloseDistance = 85.0f;

	if (pTeam)
	{
		auto pUnit = pTeam->GetUnitAtLocation(pLocation->GetPosition());


		//since when this is initialised, it will be added to the back
		//if it isn't this, then that means another unit (which would have been added earlier)
		// is in the exact same position
		if (pUnit && pUnit != this)
		{
			//Small value, should mean that movement should push them out of each other
			m_v2Position.x -= rand() % 5 + 1;
			m_v2Position.y -= rand() % 5 + 1;
		}
	}

	m_pBuilding = nullptr;


	m_pStorage = nullptr;

	m_nInventoryUpgrade = 0;

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
	bool bCollecting = false;

	//Villager logic then use unit logic
	switch (m_eAIState)
	{
	case State::CollectingResource:
		bCollecting = CollectResource(fDeltaTime);
		break;
	case State::ReturnResource:
		ReturnResource(fDeltaTime);
		break;
	case Villager::State::Building:
		Build(fDeltaTime);
		break;
	case Villager::State::Idle:

	default:
		break;
	}


	if (!bCollecting)
	{
		Unit::Update(fDeltaTime);
	}


}

void Villager::Draw(aie::Renderer2D* pRenderer)
{
	if (pRenderer)
	{
		Unit::Draw(pRenderer);
	}
}

void Villager::StartCollectingResource(Resource* pResource)
{
	m_eAIState = State::CollectingResource;
	m_pResource = pResource;
}

void Villager::SetIdle()
{
	m_eAIState = State::Idle;

}

void Villager::CreateBuilding(Building::BType eBuildingType, Vector2 v2Location)
{
	m_eAIState = State::Building;

	Tile* pTile = m_pFloor->PosToTile(v2Location);

	//If you can place a building here
	if (pTile && pTile->CanPlaceBuilding())
	{
		//Add a building
		m_pBuilding = m_pTeam->AddBuilding(eBuildingType,v2Location);

		
	}

}

void Villager::HelpBuild(Building::BType eBuildingType, Vector2 v2Location)
{
	Building* pBuilding = m_pTeam->GetBuildingAtLocation(v2Location);

	if (pBuilding)
	{
		//if this is true then that means that this is the same type of building so therefore 
		//you should just go to build this one instead of creating a whole new one
		if (pBuilding->GetBuildingType() == eBuildingType && pBuilding->GetPercentageComplete() < 100.0f)
		{
			m_pBuilding = pBuilding;
			m_eAIState = State::Building;
		}
	}

}


void Villager::Upgrade(Icon::IType eUpgrade)
{
	if (eUpgrade == Icon::IType::VillInv)
	{
		m_nInventoryUpgrade++;
	}
	else
	{
		m_nSpeUpgrade++;
	}

}

bool Villager::CollectResource(float fDeltaTime)
{
	if (m_pResource)
	{
		auto v2ToResource = m_v2Position - m_pResource->GetPosition();


		auto fDisSq = v2ToResource.magnitudeSq();

	
		//if you are far away from the resource, and haven't got a full inventory, then
		if (fDisSq > 64 * 64 && m_fCollectedCount < m_fMaximumAmount + (100 * m_nInventoryUpgrade))
		{
			m_fMiningTimer = -1.0f;



			//Get a path towards the resource
			if (m_pFloor)
			{
				MoveTo(m_pResource->GetPosition());
			}
		} 

		//If you have a full inventory
		if (m_fCollectedCount >= m_fMaximumAmount)
		{
			m_eAIState = State::ReturnResource;
			return true;

		} //you haven't got a full inventory and you are close to the resource, start collecting
		else if (fDisSq < 64 * 64)
		{
			if (m_fMiningTimer < 0.0f)
			{
				m_fMiningTimer = 0.0f;
			}
			else
			{
				m_fMiningTimer += fDeltaTime;
			}


			if (m_fMiningTimer >= m_fCycleTime)
			{
				m_fMiningTimer = 0.0f;

				m_Inventory[static_cast<int>(m_pResource->GetType())] += m_fCollectingRate;

				m_fCollectedCount += m_fCollectingRate;

				m_pResource->Collect(m_fCollectingRate);

				if (m_pResource->GetResourcesLeft() <= 0.0f)
				{
					//Get new nearby resource of same type
					m_pResource = m_pTeam->FindNearbyResource(m_v2Position, m_pResource->GetType());
				}

			}

			return true;
		}
		else if(m_pStorage)
		{

			auto pResource = m_pTeam->FindNearbyResource(m_pStorage->GetPosition(), m_pResource->GetType());

			if (m_pResource != pResource)
			{
				m_pResource = pResource;


			}
		}


	}

	return false;

}

void Villager::ReturnResource(float fDeltaTime)
{
	//go back to storage
	m_fMiningTimer = -1.0f;

	m_pStorage = m_pTeam->FindClosestStorage(m_v2Position);

	//if storage exists
	if (m_pStorage)
	{
		Vector2 v2ToStorage = m_pStorage->GetPosition() - m_v2Position;

		if (v2ToStorage.x > m_fCloseDistance || v2ToStorage.y > m_fCloseDistance || v2ToStorage.x < -m_fCloseDistance || v2ToStorage.y < -m_fCloseDistance)
		{
			MoveTo(m_pStorage->GetPosition());
		}
		else
		{
			for (int i = 0; i < static_cast<int>(Resource::Type::NoResources); i++)
			{
				m_pTeam->AddResource(static_cast<Resource::Type>(i), m_Inventory[i]);
				m_Inventory[i] = 0.0f;
			}

			m_fCollectedCount = 0.0f;

			m_eAIState = State::CollectingResource;

		}
	}



}

void Villager::Build(float fDeltaTime)
{
	if (m_pBuilding && m_pBuilding->GetPercentageComplete() < 100.0f)
	{
		auto v2ToBuilding = m_pBuilding->GetPosition() - m_v2Position;

		if (v2ToBuilding.x > m_fCloseDistance || v2ToBuilding.y > m_fCloseDistance || v2ToBuilding.x < -m_fCloseDistance || v2ToBuilding.y < -m_fCloseDistance)
		{
			MoveTo(m_pBuilding->GetPosition());
		}
		else //We are close
		{
			//Stop

			m_v2Destination = Vector2(0.0f, 0.0f);

			m_av2Path.clear();

			//This will obviously stack for every villager building this
			m_pBuilding->SetPercentageComplete(m_pBuilding->GetPercentageComplete() + (m_fBuildPercentPerSec * fDeltaTime));



		}

	}
	else  if(m_pBuilding)
	{
		if (m_pBuilding->GetBuildingType() == Building::BType::Storage)
		{
			m_eAIState = State::CollectingResource;

			m_pResource = m_pTeam->FindNearbyResource(m_v2Position, Resource::Type::NoResources);
		}
	}


}
