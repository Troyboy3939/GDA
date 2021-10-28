#pragma once
#include <string>
#include <functional>

#include "PlansOverseer.h"


class Expectation;
class Manager;


//Alias Declarations
using ExpecInitList = std::initializer_list<Expectation*>;
using Expectations = std::vector<Expectation*>;

//------------------------------------------------------
// Goal: A thing that a manager should try to work towards
//
// Must have a required world state -> For planner to work
// Must have an IsValid Function -> How would you know if you can do this if it didn't?
//
// Must have a list of expectations -> things it is assuming are true ->
// necessary for responding to unexpected events
//
// Can have any data passed into it by using pData. This could be used for
// saying specifically which thing to attack, or which thing to build
//
//------------------------------------------------------
class Goal
{
public:
	//------------------------------------
	// Constructors / Destuctors
	//------------------------------------


	//------------------------------------
	// rsReqWs = Required World State -> Must be true if this goal is completed
	// pIsValidFunction -> This will be called when the planner needs to check if this goal is valid (can be done)
	// expec = ExpecInitList. Use Initialiser list such as -> {"EnemyWeaker", "EnemyHasNoPikemen"}
	// bMitigate -> whether this goal requires a risk analysis and try to mitigate risks
	// nThreshold -> at what point is a mitigation necessary
	// pData -> Any data that is necessary for this goal to function properly
	// rsType -> The type of pData
	//------------------------------------
	Goal(std::string& rsReqWS, std::function<bool(Manager* pMan)>& IsValidFunction, ExpecInitList expec,bool bMitigate = false,PlansOverseer::RiskSeverity nThreshold = PlansOverseer::RiskSeverity::NONE, const std::string& rsType = "", void* pData = nullptr);

	virtual ~Goal();

	
	
	//------------------------------------
	// Returns the world that needs to be true 
	// for this goal to be complete
	//------------------------------------
	std::string& GetRequiredWorldState();


	//------------------------------------
	// Calls the function pointer. Determines
	// whether a goal can be completed 
	// or not
	//------------------------------------
	virtual bool IsValid(Manager* pManager);

	//------------------------------------
	// Returns the data that was passed in
	//------------------------------------
	void* GetData();

	//------------------------------------
	// Returns the type of m_pData
	//------------------------------------
	std::string& GetDataType();

	//------------------------------------
	// Changes m_pData to pData
	//------------------------------------
	void SetData(void* pData);

	//------------------------------------
	// Updates the type of m_pData
	//------------------------------------
	void SetDataType(std::string& sType);


	//------------------------------------
	// Returns reference to list of expectations
	//------------------------------------
	Expectations& GetExpectations();

	PlansOverseer::RiskSeverity GetThreshold();

	void SetThreshold(PlansOverseer::RiskSeverity nThreshold);

	bool UseRiskAnalysis();
protected:

	Expectations m_asExpectations;

	//Required world state of goal
	std::string m_sReqWorldState;

	PlansOverseer::RiskSeverity m_nThreshold;

	//function pointer to check whether the action can be completed or not
	std::function<bool(Manager* pManager)> m_fnIsValid;

	bool m_bMitigation;

	//Data passed into goal
	void* m_pData;

	

	//type of m_pData
	std::string m_sDataType;
};

