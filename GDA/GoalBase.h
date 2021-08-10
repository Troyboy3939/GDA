#pragma once
#include <string>
#include <functional>

class Manager;

class GoalBase
{
public:
	virtual ~GoalBase() = 0;

	
	

	std::string GetRequiredWorldState();


	//------------------------------------
	// Calls the function pointer. Determines
	// whether a goal can be completed 
	// or not
	//------------------------------------
	virtual bool IsValid(Manager* pManager) = 0;


	//------------------------------------
	// Resets IsValid() to another function
	//------------------------------------
	void SetIsValidFunction(std::function<bool(Manager* pManager)>* pIsValidFunction);


protected:

	
	//------------------------------------
	// Template function so that so that when 
	// data is passed in the Goal::Init()
	// it has access to the Goal::m_pData
	//------------------------------------
	template<typename Data>
	void Init(std::string sReqWS, std::function<bool(Manager* pManager, Data* pData)>* pIsValidFunction)
	{
		m_sReqWorldState = sReqWS;
		m_pIsValid = pIsValidFunction;
	}

	std::string m_sReqWorldState;


	//function pointer to check whether the action can be completed or not
	std::function<bool(Manager* pManager)>* m_pIsValid;
};

