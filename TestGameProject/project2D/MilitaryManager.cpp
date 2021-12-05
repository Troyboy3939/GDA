#include "MilitaryManager.h"

MilitaryManager::MilitaryManager(Blackboard* pBlackboard, Goal* pDefaultGoal) : Manager(pBlackboard, pDefaultGoal)
{
}

MilitaryManager::~MilitaryManager()
{
}

void MilitaryManager::SetUpGoals()
{
}

void MilitaryManager::SetUpActions()
{
}

void MilitaryManager::HandleMessage(Message* pMessage)
{
}

void MilitaryManager::Update(float fDeltaTime)
{
	Manager::Update(fDeltaTime);
}
