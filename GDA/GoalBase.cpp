#include "GoalBase.h"




GoalBase::~GoalBase()
{
}


std::string GoalBase::GetRequiredWorldState()
{
	return m_sReqWorldState;
}

