#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "ActionBase.h"
class Manager;

template<typename Data = bool>
class Action : public ActionBase
{
public:
	
	void Init(float fCost, std::function<bool(Manager* pManager, Data pData)>* pIsValidFuction, Data data = NULL)
	{
		ActionBase::Init(fCost, pIsValidFuction);

		m_Data = data;
	}



	bool IsValid(Manager* pManager)
	{
		return (*m_pIsValid)(pManager, m_Data);
	}
private:
	Data m_Data;


};

