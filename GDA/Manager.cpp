#include "Manager.h"
#include "Goal.h"
#include "Action.h"
#include "Director.h"
#include "Message.h"
#include <utility>
#include <map>
#include "Observer.h"

Manager::Manager(Messenger* pNext, GoalBase* pDefaultGoal) : Messenger(pNext)
{
	//Set up the director
	m_pDirector = new Director(this);

	//Choose a goal to 
	m_pGoal = pDefaultGoal;

	if (!pDefaultGoal)
	{
		m_pDirector->PickGoal();
	}



	//This creates a new message, that contains data of the above type. Then, pass in the data, along with who this message is for.
	//Now this message can be reused instead of created everytime a new plan is needed
	m_pPlanMessage = new Message<Manager*>(this, m_anMessageToID, "Get Plan");


	

	
}

void Manager::Update(float fDeltaTime)
{

	//check that your goal is still valid
	if (!m_pGoal->IsValid(this))
	{

	}
	else //if it isn't
	{
		//Get a new goal
		m_pDirector->PickGoal();

		//then get a plan for said goal
		GetNewPlan();
	}
}

GoalBase* Manager::GetGoal()
{
	return m_pGoal;
}

void Manager::SetGoal(GoalBase* pGoal)
{
	m_pGoal = pGoal;

	
}

void Manager::GetNewPlan()
{
	//If the next person in the messenger LL exists, and you have a goal
	if (m_pNext && m_pGoal)
	{

		//Set up the array about who this message is for
		m_anMessageToID.clear();
		m_anMessageToID.push_back(0);

		//Send the message asking for a new plan
		m_pNext->SendMessage(m_pPlanMessage);


	}

}

std::vector<ActionBase*>& Manager::GetAvailableAction()
{
	return m_apAvailableActions;
}

std::vector<ActionBase*>& Manager::GetCurrentPlan()
{
	return m_apCurrentPlan;
}

std::map<std::string, bool>& Manager::GetExpectedWS()
{
	return m_apExpectedWS;
}

std::vector<GoalBase*>& Manager::GetAvailableGoals()
{
	return m_apAvailableGoals;
}

std::map<std::string, bool>& Manager::GetCurrentWS()
{
	return m_pObserver->GetCurrentWorldState();
}
