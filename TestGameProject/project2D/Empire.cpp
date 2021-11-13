#include "Empire.h"
#include "TownCentre.h"
#include "Unit.h"
#include "Building.h"
#include "BuildingPool.h"
#include "UnitPool.h"
#include "Floor.h"
#include "ResourceManager.h"
#include "Villager.h"

Empire::Empire(BuildingPool* pBuildPool, UnitPool* pUnitPool, Floor* pFloor, ResourceManager* pReMan, Vector2 v2TcLocation, Vector3 v3Colour, Vector3 v3StartingResources, bool bAI)
{

	m_fWood = v3StartingResources.x;

	m_fFood = v3StartingResources.y;

	m_fGold = v3StartingResources.z;

	m_v3TeamColour = v3Colour;

	m_pBuildPool = pBuildPool;

	//if red
	if(v3Colour.x >= 1.0f)
	{
		m_pTcTexture = new aie::Texture("Textures/HouseRed.png");
	}
	else
	{
		m_pTcTexture = new aie::Texture("Textures/HouseBlue.png");
	}

	m_pUnitPool = pUnitPool;

	m_pResourceManager = pReMan;
	m_pFloor = pFloor;



	auto pTownCentre = static_cast<TownCentre*>(m_pBuildPool->GetBuilding(Building::BType::TownCentre));

	if (pTownCentre)
	{
		m_apBuildings.push_back(pTownCentre);

		pTownCentre->Initialise(m_pTcTexture,v2TcLocation);
	}

	//have 3 villagers to begin with
	for (int i = 0; i < 3; i++)
	{
		auto pVillager = dynamic_cast<Villager*>(m_pUnitPool->GetUnit(Unit::UType::Villager));

		Vector2 v2Pos = v2TcLocation;

		v2Pos.x += rand() % 100 + 1;
		v2Pos.x -= 50;


		v2Pos.y -= rand() % 50 + 1;
		v2Pos.y -= 100;

		pVillager->Initialise(v2Pos, this, 100.0f,10.0f, 5.0f);

		m_apUnits.push_back(pVillager);
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
		m_apUnits[i]->Update(fDeltaTime);
	}

	//update buildings
	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		m_apBuildings[i]->Update(fDeltaTime);
	}

}

void Empire::Draw(aie::Renderer2D* pRenderer)
{

	//Draw units
	for (int i = 0; i < m_apUnits.size(); i++)
	{
		m_apUnits[i]->Draw(pRenderer);
	}

	//draw buildings
	for (int i = 0; i < m_apBuildings.size(); i++)
	{
		m_apBuildings[i]->Draw(pRenderer);
	}
}
