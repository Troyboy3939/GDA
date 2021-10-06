#pragma once
#include <unordered_map>
#include <string>
#include "GroupingStructures.h"

class Manager;

using WorldStateMap = std::unordered_map<std::string, bool>;
using Deviation = std::unordered_map<const std::string, bool>::iterator;
class Observer
{
public:
	//Alias Declaration.
	

	Observer(Manager* pManager);
	virtual ~Observer() = 0;



	//-----------------------------------------------
	// Return a references to the world state
	//-----------------------------------------------
	WorldStateMap& GetCurrentWorldState();

	//-----------------------------------------------
	// Called Every frame
	//-----------------------------------------------
	virtual void Update(float fDeltaTime);

	//-----------------------------------------------
	// Looks for differences between Expected and
	// current world state, returns the deviation
	//-----------------------------------------------
	const Deviation DeviationChecker();

	//-----------------------------------------------
	// Compares the current world state to expected
	// world state
	//-----------------------------------------------
	 bool CheckDeviation(const std::string& rsWorldState);


private:
	 void FindExpectedWorldState();

	WorldStateMap m_aCurrentWorldState;
	WorldStateMap m_aExpectedWorldState;

	Manager* m_pManager;
};

