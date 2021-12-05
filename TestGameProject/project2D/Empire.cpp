#include "Empire.h"
#include "TownCentre.h"
#include "Unit.h"
#include "Building.h"
#include "BuildingPool.h"
#include "UnitPool.h"
#include "Floor.h"
#include "ResourceManager.h"
#include "Villager.h"
#include "PlayerComponent.h"
#include "AIComponent.h"
#include "Storage.h"
#include "Barracks.h"
#include "Stable.h"
#include "ArcheryRange.h"
#include "Swordsman.h"
#include "Pikeman.h"
#include "Knight.h"
#include "Scout.h"
#include "Archer.h"
#include "Skirmisher.h"
#include <ctime>

Empire::Empire(BuildingPool* pBuildPool, UnitPool* pUnitPool, Floor* pFloor, ResourceManager* pReMan, Vector2 v2TcLocation, Vector3 v3Colour, Vector3 v3StartingResources, bool bAI)
{

	m_fWood = v3StartingResources.x;

	m_fFood = v3StartingResources.y;

	m_fGold = v3StartingResources.z;

	m_v3TeamColour = v3Colour;

	m_pBuildPool = pBuildPool;
	srand(time(NULL));
	//if red
	if(v3Colour.x >= 1.0f)
	{
		m_pTcTexture = new aie::Texture("Textures/HouseRed.png");
		m_pArTexture = new aie::Texture("Textures/ArcheryRangeRed.png");;
		m_pBaTexture = new aie::Texture("Textures/BarracksRed.png");;
		m_pStoTexture = new aie::Texture("Textures/StorageRed.png");;
		m_pStaTexture = new aie::Texture("Textures/StableRed.png");;
	}
	else
	{
		m_pTcTexture = new aie::Texture("Textures/HouseBlue.png");
		m_pArTexture = new aie::Texture("Textures/ArcheryRangeBlue.png");;
		m_pBaTexture = new aie::Texture("Textures/BarracksBlue.png");;
		m_pStoTexture = new aie::Texture("Textures/StorageBlue.png");;
		m_pStaTexture = new aie::Texture("Textures/StableBlue.png");;
	}

	m_pUnitPool = pUnitPool;

	m_pResourceManager = pReMan;
	m_pFloor = pFloor;

	m_nAge = 1;

	auto pTownCentre = static_cast<TownCentre*>(m_pBuildPool->GetBuilding(Building::BType::TownCentre));

	if (pTownCentre)
	{
		m_apBuildings.push_back(pTownCentre);


		pTownCentre->Initialise(m_pTcTexture,m_pFloor->PosToTile(v2TcLocation),this,Vector3());


		pTownCentre->SetPercentageComplete(100.0f);
	}

	//have 3 villagers to begin with
	for (int i = 0; i < 3; i++)
	{
		AddVillager(v2TcLocation);
	}


	if (bAI)
	{
		m_pInputComponent = new AIComponent(this);
	}
	else
	{
		m_pInputComponent = new PlayerComponent(this);
	}


}

Empire::~Empire()
{

	if (m_pTcTexture)
	{
		delete m_pTcTexture;

		m_pTcTexture = nullptr;
	}

}

void Empire::SetTeamColour(Vector3 v3Colour)
{
	m_v3TeamColour = v3Colour;
}

Vector3& Empire::GetTeamColour()
{
	return m_v3TeamColour;
}

Floor* Empire::GetFloor()
{
	return m_pFloor;
}

ResourceManager* Empire::GetResourceManager()
{
	return m_pResourceManager;
}

void Empire::Update(float fDeltaTime)
{
	//Update units
	for (int i = 0; i < m_apUnits.size(); i++)
	{
		if (m_apUnits[i])
		{
			m_apUnits[i]->Update(fDeltaTime);
		}
	}

	//update buildings
	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		if (m_apBuildings[i])
		{
			m_apBuildings[i]->Update(fDeltaTime);
		}
	}

	if (m_pInputComponent)
	{
		m_pInputComponent->Update(fDeltaTime);
	}

}

void Empire::Draw(aie::Renderer2D* pRenderer)
{

	//Draw units
	for (int i = 0; i < m_apUnits.size(); i++)
	{
		if (m_apUnits[i])
		{
			m_apUnits[i]->Draw(pRenderer);
		}
	}

	//draw buildings
	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		if (m_apBuildings[i])
		{
			m_apBuildings[i]->Draw(pRenderer);
		}
	}

	if (m_pInputComponent)
	{
		m_pInputComponent->Draw(pRenderer);
	}
}

Unit* Empire::GetUnitAtLocation(Vector2 v2Location)
{

	for (int i = 0; i < m_apUnits.size(); i++)
	{
		if (m_apUnits[i])
		{

			Vector2 v2Length = v2Location - m_apUnits[i]->GetPosition();

			if (v2Length.magnitudeSq() < m_apUnits[i]->GetRadius() * m_apUnits[i]->GetRadius())
			{
				return m_apUnits[i];
			}
		}
	}


	return nullptr;
}

Building* Empire::GetBuildingAtLocation(Vector2 v2Location)
{
	


	for (auto pBuilding : m_apBuildings)
	{
		if (pBuilding)
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

Building* Empire::GetBuildingAtLocation(Tile* pLocation)
{

	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		if (m_apBuildings[i] && m_apBuildings[i]->GetTile() == pLocation)
		{
			return m_apBuildings[i];
		}
	}

	return nullptr;
}

void Empire::GetUnitsWithBounds(Vector2 v2From, Vector2 v2To, std::vector<Unit*>& rapSelectedUnits)
{
	rapSelectedUnits.clear();
	float fXMinimum;
	float fXMaximum;


	float fYMinimum;
	float fYMaximum;

	if (v2From.x > v2To.x)
	{
		fXMinimum = v2To.x;
		fXMaximum = v2From.x;
	}
	else
	{
		fXMinimum = v2From.x;
		fXMaximum = v2To.x;
	}
	if (v2From.y > v2To.y)
	{
		fYMinimum = v2To.y;
		fYMaximum = v2From.y;
	}
	else
	{
		fYMinimum = v2From.y;
		fYMaximum = v2To.y;
	}



	for (int i = 0; i < m_apUnits.size(); i++)
	{
		auto pUnit = m_apUnits[i];

		if (pUnit)
		{
		
			auto v2Positon = pUnit->GetPosition();

			if (v2Positon.x >= fXMinimum && v2Positon.x <= fXMaximum && v2Positon.y >= fYMinimum && v2Positon.y <= fYMaximum)
			{
				rapSelectedUnits.push_back(pUnit);
			}

		}
	}

}

Resource* Empire::GetResourceAtLocation(Vector2 v2Location)
{
	return nullptr;
}

Resource* Empire::FindNearbyResource(Vector2 v2Location, Resource::Type eType)
{
	return m_pResourceManager->GetClosestResource(v2Location,  eType);
}

Building* Empire::FindClosestStorage(Vector2 v2Location)
{
	Building* pClosest = nullptr;

	float fDistance = 0.0f;

	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		if (m_apBuildings[i] && static_cast<int>(m_apBuildings[i]->GetBuildingType()) < 2 )
		{
			Vector2 v2ToBuilding = m_apBuildings[i]->GetPosition() - v2Location;

			
			if (m_apBuildings[i]->GetPercentageComplete() < 100.0f)
			{
				continue;
			}


			if (pClosest)
			{
				

				if (fDistance > v2ToBuilding.magnitudeSq())
				{
					fDistance = v2ToBuilding.magnitudeSq();
					pClosest = m_apBuildings[i];
				}
			}
			else
			{
				pClosest = m_apBuildings[i];
				fDistance = v2ToBuilding.magnitudeSq();
			}
		}
	}



	return pClosest;
}

void Empire::AddVillager(Vector2 v2TCLoc)
{
	auto pVillager = dynamic_cast<Villager*>(m_pUnitPool->GetUnit(Unit::UType::Villager));

	Vector2 v2Pos = v2TCLoc;

	auto pTile = m_pFloor->PosToTile(v2Pos);

	pTile = pTile->GetNeighbour(Tile::Connection::Down);

	if (pTile)
	{
		v2Pos = pTile->GetPosition();
	}

	

	v2Pos.x += rand() % 100 + 1;
	v2Pos.x -= 50;


	v2Pos.y -= rand() % 50 + 1;
	v2Pos.y -= 50;

	
	pTile = m_pFloor->PosToTile(v2Pos);

	pVillager->Initialise(pTile, this, 40.0f, 10.0f, 5.0f);

	m_apUnits.push_back(pVillager);


}

void Empire::CreateUnit(Vector2 v2BuildingLocation, Unit::UType eType)
{


	auto pUnit = m_pUnitPool->GetUnit(eType);

	Vector2 v2Pos = v2BuildingLocation;

	v2Pos.x += rand() % 100 + 1;
	v2Pos.x -= 50;


	v2Pos.y -= rand() % 50 + 1;
	v2Pos.y -= 100;

	switch (eType)
	{
	case Unit::UType::Villager:
	{
		auto pVill = static_cast<Villager*>(pUnit);
		pVill->Initialise(m_pFloor->PosToTile(v2Pos), this,40.0f,10.0f,5.0f);
		break;
	}
	case Unit::UType::Knight:
	{
		auto pKnight = static_cast<Knight*>(pUnit);
		pKnight->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::Scout:
	{
		auto pScout = static_cast<Scout*>(pUnit);
		pScout->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::Skirmisher:
	{
		auto pSkirmisher = static_cast<Skirmisher*>(pUnit);
		pSkirmisher->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::Archer:
	{
		auto pArcher = static_cast<Archer*>(pUnit);
		pArcher->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::Swordsman:
	{
		auto pSwordsman = static_cast<Swordsman*>(pUnit);
		pSwordsman->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::Pikeman:
	{
		auto pPikeman = static_cast<Pikeman*>(pUnit);
		pPikeman->Initialise(m_pFloor->PosToTile(v2Pos), this);
	}
		break;
	case Unit::UType::NoUnitTypes:
		break;
	default:
		break;
	}


	m_apUnits.push_back(pUnit);
}

float Empire::GetGold()
{
	return m_fGold;
}

float Empire::GetWood()
{
	return m_fWood;
}

float Empire::GetFood()
{
	return m_fFood;
}

void Empire::SetFood(float fFood)
{
	m_fFood = fFood;
}

void Empire::SetWood(float fWood)
{
	m_fWood = fWood;
}

void Empire::SetGold(float fGold)
{
	m_fGold = fGold;
}

void Empire::SpendResources(Vector3 v3Amount)
{
	m_fWood -= v3Amount.x;
	m_fFood -= v3Amount.y;
	m_fGold -= v3Amount.z;

}

void Empire::AddResource(Resource::Type eType, float fAmount)
{
	switch (eType)
	{
	case Resource::Type::WOOD:
		m_fWood += fAmount;
		break;
	case Resource::Type::GOLD:
		m_fGold += fAmount;
		break;
	case Resource::Type::FOOD:
		m_fFood += fAmount;
		break;
	}
}

Building* Empire::AddBuilding(Building::BType eType, Vector2 v2Location)
{
	Building* pBuilding = m_pBuildPool->GetBuilding(eType);

	if (pBuilding)
	{

		aie::Texture* pTexture = nullptr;

		auto v3Cost = Vector3();

		switch (eType)
		{
		case Building::BType::TownCentre:
		{
			pTexture = m_pTcTexture;
			v3Cost.x = 300.0f;
			v3Cost.z = 200.0f;
			static_cast<TownCentre*>(pBuilding)->Initialise(pTexture, m_pFloor->PosToTile(v2Location), this, v3Cost);
		}
		break;
		case Building::BType::Storage:
		{
			pTexture = m_pStoTexture;
			v3Cost.x = 100.0f;
			static_cast<Storage*>(pBuilding)->Initialise(pTexture, m_pFloor->PosToTile(v2Location), this, v3Cost);
		}
		break;
		case Building::BType::Barracks:
		{
			v3Cost.x = 150.0f;
			v3Cost.z = 100.0f;
			pTexture = m_pBaTexture;
			static_cast<Barracks*>(pBuilding)->Initialise(pTexture, m_pFloor->PosToTile(v2Location), this, v3Cost);
		}
		break;
		case Building::BType::ArcheryRange:
		{
			v3Cost.x = 150.0f;
			v3Cost.z = 100.0f;
			pTexture = m_pArTexture;
			static_cast<ArcheryRange*>(pBuilding)->Initialise(pTexture, m_pFloor->PosToTile(v2Location), this, v3Cost);
		}
		break;
		case Building::BType::Stable:
		{
			v3Cost.x = 150.0f;
			v3Cost.y = 50.0f;
			v3Cost.z = 100.0f;
			pTexture = m_pStaTexture;
			static_cast<Stable*>(pBuilding)->Initialise(pTexture, m_pFloor->PosToTile(v2Location), this, v3Cost);
		}
		break;
		case Building::BType::NoTypes:
			break;
		default:
			break;
		}


		m_apBuildings.push_back(pBuilding);

		return pBuilding;
	}
		return nullptr;
}

TownCentre* Empire::GetTownCentre()
{
	for (auto pBuilding : m_apBuildings)
	{
		if (pBuilding && pBuilding->GetBuildingType() == Building::BType::TownCentre)
		{
			return static_cast<TownCentre*>(pBuilding);
		}
	}



	return nullptr;
}

void Empire::UpgradeUnit(Icon::IType eUpgrade)
{

	//for every unit, go through and apply the upgrade to the appropriate units

	for (auto pUnit : m_apUnits)
	{
		if (pUnit)
		{
			switch (eUpgrade)
			{
			case Icon::IType::VillSpee:
			case Icon::IType::VillInv:
			{
				if (pUnit->GetUnitType() == Unit::UType::Villager)
				{
					pUnit->Upgrade(eUpgrade);
				}
			}
				break;
			case Icon::IType::InfAtt:
			case Icon::IType::InfDef:
			case Icon::IType::InfSpe:
			{
				if (pUnit->GetUnitType() == Unit::UType::Swordsman || pUnit->GetUnitType() == Unit::UType::Pikeman)
				{
					pUnit->Upgrade(eUpgrade);
				}
			}
				break;
			case Icon::IType::ArcAtt:
			case Icon::IType::ArcDef:
			case Icon::IType::ArcSpe:
			{
				if (pUnit->GetUnitType() == Unit::UType::Archer || pUnit->GetUnitType() == Unit::UType::Skirmisher)
				{
					pUnit->Upgrade(eUpgrade);
				}
			}
				break;
			case Icon::IType::CavAtt:
			case Icon::IType::CavDef:
			case Icon::IType::CavSpe:
			{
				if (pUnit->GetUnitType() == Unit::UType::Scout || pUnit->GetUnitType() == Unit::UType::Knight)
				{
					pUnit->Upgrade(eUpgrade);
				}
			}
				break;
			default:
				break;
			}
		}
	}

}



bool Empire::CanPerformAction(Icon* pIcon, bool bIncrement)
{


	//if you have enough resources, and you are the required age
	if (m_fFood >= pIcon->GetFoodCost() && m_fGold >= pIcon->GetGoldCost() && m_fWood >= pIcon->GetWoodCost() && m_nAge >= pIcon->GetRequiredAge())
	{
		
		//increment the amount of upgrades you have if its an upgrade, or if you have done it too many times this age 

		switch (pIcon->GetIconType())
		{
			//if an upgrade or age up

			case Icon::IType::AgeUp:
			{
				return  m_nAge < 3;
			}
			case Icon::IType::VillSpee:
			case Icon::IType::VillInv:
			case Icon::IType::InfAtt:
			case Icon::IType::InfDef:
			case Icon::IType::InfSpe:
			case Icon::IType::ArcAtt:
			case Icon::IType::ArcDef:
			case Icon::IType::ArcSpe:
			case Icon::IType::CavAtt:
			case Icon::IType::CavDef:
			case Icon::IType::CavSpe:
			{
					if (m_Upgrades[pIcon] < m_nAge)
					{
						if (bIncrement)
						{
							m_Upgrades[pIcon]++;
						}
						return true;
					}
					return false;
				
						return true;
				
			}
				break;
			default:
				return true;
			;
		}
	}

	
	return false;
}

UnitPool* Empire::GetUnitPool()
{
	return m_pUnitPool;
}

BuildingPool* Empire::GetBuildPool()
{
	return m_pBuildPool;
}

void Empire::ReturnUnit(Unit* pUnit)
{

	m_apUnits.erase(std::remove(m_apUnits.begin(),m_apUnits.end(),pUnit),m_apUnits.end());

	m_pUnitPool->Return(pUnit);


}

void Empire::ReturnBuilding(Building* pUnit)
{
	m_apBuildings.erase(std::remove(m_apBuildings.begin(), m_apBuildings.end(),pUnit), m_apBuildings.end());
	m_pBuildPool->Return(pUnit);
}

bool Empire::HasBuilding(Building::BType eType)
{
	for (auto pBuilding : m_apBuildings)
	{
		if (pBuilding && pBuilding->GetBuildingType() == eType)
		{
			return true;
		}
	}


	return false;
}

int Empire::GetAge()
{
	return m_nAge;
}

void Empire::SetAge(int nAge)
{
	m_nAge = nAge;

	if (m_nAge > 3)
	{
		m_nAge = 3;
	}
}

Unit* Empire::GetLatestUnit(Unit::UType eType)
{
	for (int i = m_apUnits.size() - 1; i >= 0; i--)
	{
		if (m_apUnits[i] && m_apUnits[i]->GetUnitType() == eType)
		{
			return m_apUnits[i];
		}
	}


	return nullptr;
}

int Empire::GetUnitCount()
{
	return m_apUnits.size();
}

std::vector<Unit*>& Empire::GetUnits()
{
	return m_apUnits;
}

Villager* Empire::GetIdleVillager()
{

	for (auto pUnit :  m_apUnits)
	{
		if (pUnit && pUnit->GetUnitType() == Unit::UType::Villager)
		{
			auto pVill = static_cast<Villager*>(pUnit);

			if (pVill->GetState() == Villager::State::Idle)
			{
				return pVill;
			}
		}
	}


	return nullptr;
}



