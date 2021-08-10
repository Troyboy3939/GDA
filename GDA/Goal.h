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
	// Initialiser
	//------------------------------------
	void Init(std::string sReqWS, std::function<bool(Manager* pManager, Data* pData)>* pIsValidFunction, Data* pData = nullptr) 
	{

		std::function<bool(Manager* pManager, Data* pData)> pIsVal = [pIsValidFunction](Manager* pManager, Data* pData) -> bool { return pIsValidFunction(pManager, pData); };


		GoalBase::Init(sReqWS, pIsVal);

		m_pData = pData;
	}

	Data* GetData()
	{
		return m_pData;
	}

	void SetData(Data* pData)
	{
		m_pData = pData;
	}

	bool IsValid(Manager* pManager)
	{
		return (*m_pIsValid)(pManager,m_pData);
	}

private:
	Data* m_pData;
};

