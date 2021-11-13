#pragma once
#include "GameObject.h"
#include <unordered_map>
#include "Unit.h"


class Resource;
class Empire;


class Villager : public Unit
{
public:

	enum class State
	{
		MiningGold,
		CuttingWood,
		PickingBerries,
		Building,
		Idle
	};



	//Constructor exists so they can be set from the get go if needed
	Villager(Vector2 v2Location, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime);

	//Will be needed for an object pool
	Villager();

	~Villager();


	//Will be needed to initialise object for use when receiving from object pool
	void Initialise(Vector2 v2Pos, Empire* pTeam, float fMaxAmount, float fRate, float fCycleTime);

	//Updates the logic of this every frame
	void Update(float fDeltaTime);

	//Draws something every frame
	void Draw(aie::Renderer2D* pRenderer);

private:
	
	//Position that the Villager is working at
	Vector2 m_v2Working;

	//controls what the AI is doing
	State m_eAIState;

	//What resource the villager may be mining
	Resource* m_pResource;

	void AddResource(Resource* pResource);

	//How many resources the villager has collected
	//int is the type of resource, float is how many resource they have collected
	std::unordered_map<int, float> m_Inventory;

	//How many resources in total the villager is holding
	float m_fCollectedCount;

	//The maximum amount of resources the villager can have
	float m_fMaximumAmount;

	//How many resources the villager can collect every cycle
	float m_fCollectingRate;

	//Time it takes to add a resource
	float m_fCycleTime;

	//how long the villager has been mining for
	float m_fTimer;
};

