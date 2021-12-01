#pragma once
#include "Unit.h"
#include <unordered_map>

class Villager;


class UnitPool
{
public:
	UnitPool(int nAmountPerUnit);
	~UnitPool();

	//Returns a unit of that type
	Unit* GetUnit(Unit::UType eType);

	void Return(Unit* pUnit);

	std::vector<Unit*>& GetPool();

	Unit* GetUnitAtLocation(Vector2 v2Location);

	//Returns a unit that is close to pUnit, but not on pExclusion
	Unit* GetClosestUnit(Unit* pUnit, float fRadius ,Empire* pExclusion = nullptr);
private:

	Unit* CreateUnit(Unit::UType eType);

	std::vector<Unit*> m_apPool;

	std::unordered_map<Unit*, bool> m_aInUse;
	
	int m_nDefaultAmount;
};

