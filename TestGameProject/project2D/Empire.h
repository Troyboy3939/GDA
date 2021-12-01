#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include "Renderer2D.h"
#include "ResourceClass.h"
#include "Building.h"
#include "Unit.h"


//Forward declarations
class BuildingPool;
class UnitPool;


class Building;
class Floor;
class ResourceManager;
class Resource;
class InputComponent;


class Empire
{
public:
	//--------------------------------
	// 	Vectors:
	// 	   Tc -> Town Centre Location
	// 	   Colour -> Team Colour -> R = x, G = y, B = z
	// 	   StartResources -> x = wood, y = food, z = gold
	//--------------------------------
	Empire(BuildingPool* pBuildPool, UnitPool* pUnitPool ,Floor* pFloor, ResourceManager* pReMan, Vector2 v2TcLocation, Vector3 v3Colour,Vector3 v3StartingResources , bool bAI = false);
	~Empire();

	//---------------------------------------------
	// Sets the team colour of the empire 
	// Team Colour -> R = x, G = y, B = z
	//---------------------------------------------
	void SetTeamColour(Vector3 v3Colour);

	//---------------------------------------------
	// Gets the team colour of the empire 
	// Team Colour -> R = x, G = y, B = z
	//---------------------------------------------
	Vector3& GetTeamColour();


	//---------------------------------------------
	//  Returns the floor used for pathfinding
	//---------------------------------------------
	Floor* GetFloor();


	//---------------------------------------------
	// 	Returns the resource manager
	//---------------------------------------------
	ResourceManager* GetResourceManager();

	//---------------------------------------------
	// Updates logic every frame
	//---------------------------------------------
	void Update(float fDeltaTime);


	//---------------------------------------------
	// Draws graphics every frame
	//---------------------------------------------
	void Draw(aie::Renderer2D* pRenderer);

	//---------------------------------------------
	// 	Checks if a unit is at a location
	//---------------------------------------------
	Unit* GetUnitAtLocation(Vector2 v2Location);

	Building* GetBuildingAtLocation(Vector2 v2Location);
	Building* GetBuildingAtLocation(Tile* pLocation);

	//---------------------------------------------
	// 	Checks if a unit is within the range given
	//---------------------------------------------
	void GetUnitsWithBounds(Vector2 v2From, Vector2 v2To ,std::vector<Unit*>& rapSelectedUnits);

	//---------------------------------------------
	// 	Checks if a resource is at a location
	//---------------------------------------------
	Resource* GetResourceAtLocation(Vector2 v2Location);


	//---------------------------------------------
	// 	   Returns an available resource nearby
	//---------------------------------------------
	Resource* FindNearbyResource(Vector2 v2Location, Resource::Type eType);

	//---------------------------------------------
	// 
	//---------------------------------------------
	Building* FindClosestStorage(Vector2 v2Location);

	void AddVillager(Vector2 v2TCLoc);

	void CreateUnit(Vector2 v2BuildingLocation, Unit::UType eType);


	float GetGold();
	float GetWood();
	float GetFood();

	void SetFood(float fFood);
	void SetWood(float fWood);
	void SetGold(float fGold);

	void SpendResources(Vector3 v3Amount);


	void AddResource(Resource::Type eType , float fAmount);

	Building* AddBuilding(Building::BType eType, Vector2 v2Location);


	void UpgradeUnit(Icon::IType eUpgrade);

	bool CanPerformAction(Icon* pIcon, bool bIncrement = true);

	UnitPool* GetUnitPool();
	BuildingPool* GetBuildPool();
	
	void ReturnUnit(Unit* pUnit);
	void ReturnBuilding(Building* pUnit);


	int GetAge();
	void SetAge(int nAge);
private:
	//resources
	float m_fGold;
	float m_fFood;
	float m_fWood;

	//Textures for buildings
	aie::Texture* m_pTcTexture;
	aie::Texture* m_pArTexture;
	aie::Texture* m_pBaTexture;
	aie::Texture* m_pStoTexture;
	aie::Texture* m_pStaTexture;

	//What colour to draw the units and buildings
	Vector3 m_v3TeamColour;

	//list of what building and units we have
	std::vector<Unit*> m_apUnits;
	std::vector<Building*> m_apBuildings;

	//Pools to get units from
	BuildingPool* m_pBuildPool;
	UnitPool* m_pUnitPool;

	//Managers in case they are needed
	ResourceManager* m_pResourceManager;
	Floor* m_pFloor;
	InputComponent* m_pInputComponent;


	std::unordered_map<Icon*, int> m_Upgrades;
	

	int m_nAge;
};

