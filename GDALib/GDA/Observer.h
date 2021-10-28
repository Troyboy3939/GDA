#pragma once
#include <unordered_map>
#include <string>

#include "Action.h"
#include "GroupingStructures.h"
#include "Goal.h"
#include "Message.h"


class Manager;
class Expectation;

//list of references to strings
using RefStringList = std::vector<std::string>;
using ExplanationMap = std::unordered_multimap<Expectation*, std::string>;

//alias declarations -> easier to read and write
using WorldStateMap = std::unordered_map<std::string, bool>;
class Observer
{
public:

	//-------------------------------------------------------------------------
	// Public Functions
	//-------------------------------------------------------------------------


	Observer(Manager* pManager);
	virtual ~Observer();


	//-----------------------------------------------
	// Called Every frame
	//-----------------------------------------------
	virtual void Update(float fDeltaTime);





	Manager* GetManager();


	RefStringList& GetExplanations();


	void AddExplanation(Expectation* pExpect, std::string& rsExplanation);

	ExplanationMap& GetExplanationMap();

private:



	//-------------------------------------------------------------------------
	// Protected Functions
	//-------------------------------------------------------------------------


	void GenerateExplanation();



	//-----------------------------------------------
	// Looks for differences between Expected and
	// current world state, returns the deviation
	//-----------------------------------------------
	void FindDeviations();




	//-------------------------------------------------------------------------
	// Private Variables
	//-------------------------------------------------------------------------


	//list of references to explanations
	RefStringList m_arsExplanations;

	//Map expectations to explanations
	ExplanationMap m_ExplanationMap;

	Message* m_pExplanationMessage;

	Recipients m_anRecipients;

	Expectations m_apDeviations;

	Manager* m_pManager;
};

