#pragma once
#include <string>
#include <functional>

class Manager;

class Goal
{
public:
	//------------------------------------
	// Constructors / Destuctors
	//------------------------------------

	Goal(std::string& rsReqWS, std::function<bool(Manager* pManager)>* pIsValidFunction, std::string& rsType ,void* pData = nullptr);

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


protected:

	//Required world state of goal
	std::string m_sReqWorldState;


	//function pointer to check whether the action can be completed or not
	std::function<bool(Manager* pManager)>* m_pIsValid;

	//Data passed into goal
	void* m_pData;

	//type of m_pData
	std::string m_sDataType;
};

