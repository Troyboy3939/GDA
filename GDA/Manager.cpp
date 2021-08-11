#include "Manager.h"
#include "Goal.h"
#include "Action.h"
#include "Director.h"
#include "Message.h"
#include <utility>
#include <map>


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

	//sorry for this disgusting mess
	// Basically create pointer to a Quad Class. This is a template class that takes any 4 types and stores them. This stores the necessary information to get a plan
	m_pPlanData = new Quad<Manager*, std::vector<ActionBase*>&, std::vector<ActionBase*>&, std::map<std::string, bool>&>(this, m_apCurrentPlan,m_apAvailableActions,m_apExpectedWS);

	//This creates a new message, that contains data of the above type. Then, pass in the data, along with who this message is for.
	//Now this message can be reused instead of created everytime a new plan is needed
	m_pPlanMessage = new Message<Quad<Manager*, std::vector<ActionBase*>&, std::vector<ActionBase*>&, std::map<std::string, bool>&>>(m_pPlanData, m_anMessageToID, "Get Plan");


	

	
}

void Manager::Update(float fDeltaTime)
{
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
