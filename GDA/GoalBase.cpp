#include "GoalBase.h"




GoalBase::~GoalBase()
{
}


std::string GoalBase::GetRequiredWorldState()
{
	return m_sReqWorldState;
}



void GoalBase::SetIsValidFunction(std::function<bool(Manager* pManager)>* pIsValidFunction)
{
	m_pIsValid = pIsValidFunction;
}
