#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <vector>
#include "Renderer2D.h"

//Forward declarations
class BuildingPool;
class UnitPool;


class Building;
class Unit;
class Floor;
class ResourceManager;

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

private:
	float m_fGold;
	float m_fFood;
	float m_fWood;

	aie::Texture* m_pTcTexture;

	Vector3 m_v3TeamColour;

	std::vector<Unit*> m_apUnits;

	std::vector<Building*> m_apBuildings;

	BuildingPool* m_pBuildPool;

	UnitPool* m_pUnitPool;

	ResourceManager* m_pResourceManager;
	Floor* m_pFloor;
};

