#pragma once
#include "Building.h"
#include <unordered_map>
#include <vector>

class BuildingPool
{
public:
	BuildingPool(int nDefaultAmount);
	~BuildingPool();

	Building* GetBuilding(Building::BType eType);

	void Return(Building* pBuilding);

private:

	Building* CreateBuilding(Building::BType eType);


	std::vector<Building*> m_apPool;

	std::unordered_map<Building*, bool> m_aInUse;

	int m_nDefaultAmount;

};

