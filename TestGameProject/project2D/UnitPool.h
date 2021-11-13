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



private:

	Unit* CreateUnit(Unit::UType eType);

	std::vector<Unit*> m_apPool;

	std::unordered_map<Unit*, bool> m_aInUse;
	
	int m_nDefaultAmount;
};

