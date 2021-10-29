#pragma once
#include "GameObject.h"
#include <unordered_map>

class Resource;

class Villager : GameObject
{
public:
	Villager(Vector2 v2Pos, bool nTeam, float fMaxAmount, float fRate, float fCycleTime);

	void AddResource(Resource* pResource);

	void Update(float fDeltaTime);

	void Draw(aie::Renderer2D* pRenderer);

private:
	std::unordered_map<int, float> m_Inventory;

	bool m_bTeam;

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

