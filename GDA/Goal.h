#pragma once
#include <string>
#include <functional>
#include "GoalBase.h"
class Manager;

template<typename Data = bool>
class Goal : public GoalBase
{
public:

	//------------------------------------
	// Empty Constructor. Has to be initialised 
	// using Init()
	//------------------------------------
	Goal()
	{

	}
	

	//------------------------------------
	// Destructor
	//------------------------------------
	~Goal()
	{

	}

	//------------------------------------
	// Initialiser. NULL in case non-pointer value passed in
	//------------------------------------
	void Init(std::string sReqWS, std::function<bool(Manager* pManager, Data* pData)>* pIsValidFunction, Data data = NULL) 
	{

		GoalBase::Init(sReqWS, pIsValidFunction);

		m_Data = data;
	}

	Data* GetData()
	{
		return m_Data;
	}

	void SetData(Data data)
	{
		m_Data = data;
	}

	bool IsValid(Manager* pManager)
	{
		return (*m_pIsValid)(pManager,m_Data);
	}

private:
	Data m_Data;
};

