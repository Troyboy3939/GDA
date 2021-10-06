#pragma once
#include <unordered_map>
#include <string>

#include "Action.h"
#include "GroupingStructures.h"

class Manager;

//alias declarations -> easier to read and write
using WorldStateMap = std::unordered_map<std::string, bool>;
using Deviation = std::pair<std::string,bool>;

class Observer
{
public:

	//-------------------------------------------------------------------------
	// Public Functions
	//-------------------------------------------------------------------------


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

protected:



	//-------------------------------------------------------------------------
	// Protected Functions
	//-------------------------------------------------------------------------


	std::string& GenerateExplanation();



	//-----------------------------------------------
	// Looks for differences between Expected and
	// current world state, returns the deviation
	//-----------------------------------------------
	void FindDeviations();



	//-----------------------------------------------
	// Compares the current world state to expected
	// world state
	//-----------------------------------------------
	 bool CheckDeviation(const std::string& rsWorldState);

	//TODO: Potentially optimise this function
	//Try not to call this function a lot -> could cause slow performance
	 void FindExpectedWorldState();


	//-------------------------------------------------------------------------
	// Private Variables
	//-------------------------------------------------------------------------

	//Set this to true when
	//
	bool m_bWSUpdated;

	int m_nCurrentAction;

	WorldStateMap m_aCurrentWorldState;
	WorldStateMap m_aExpectedWorldState;


	

	//stored here so that it doesn't
	//have to get remade every time
	//FindExpectedWS is called
	std::vector<std::string&> m_arsSatisfiedWS;


	std::vector<Deviation> m_apDeviations;

	Manager* m_pManager;
};

