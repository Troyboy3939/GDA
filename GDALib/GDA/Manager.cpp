#include "Manager.h"
#include "Goal.h"
#include "Action.h"
#include "Director.h"
#include "Message.h"
#include <utility>
#include <map>
#include "Observer.h"
#include "Blackboard.h"


Manager::Manager(Blackboard* pBlackboard, Goal* pDefaultGoal) : Messenger(pBlackboard)
{
	//Set up the director
	m_pDirector = new Director(this,0);

	m_bNewGoal = false;

	//if it exists
	if(m_pBlackboard)
	{
		m_pBlackboard->AddManager(this);
	}

	//Choose a goal to 
	m_pGoal = pDefaultGoal;

	if (!pDefaultGoal)
	{
		m_pDirector->PickGoal();
	}
	
	m_anMessageToID.push_back(0);

	m_pCurrentWS = new Message(m_anMessageToID,"Get World State", this, "Manager*");

	//This creates a new message, meant for the plans overseer, passing in a pointer to this manager
	m_pPlanMessage = new Message(m_anMessageToID,"Ra Plan",this,"Manager*");

	m_pMitigationMessage = new Message(m_anMessageToID,"Mitigation",this,"Manager*");


	
}

Manager::~Manager()
{
	if(m_pDirector)
	{
		delete m_pDirector;
		m_pDirector = nullptr;
	}

	if(m_pCurrentWS)
	{
		delete m_pCurrentWS;
		m_pCurrentWS = nullptr;
	}

	if(m_pPlanMessage)
	{
		delete m_pPlanMessage;
		m_pPlanMessage = nullptr;
	}

	if(m_pMitigationMessage)
	{
		delete m_pMitigationMessage;
		m_pMitigationMessage = nullptr;
	}
}

void Manager::Update(float fDeltaTime)
{

	//check that your goal is still valid
	if (!m_pGoal->IsValid(this) || m_bNewGoal)
	{
		//Get a new goal
		m_pDirector->PickGoal();

		//then get a plan for said goal
		GetNewPlan();

		m_bNewGoal = false;
	}
	else if (!m_bNewGoal && m_pMitigation && m_apMitigationPlan.empty() && m_pBlackboard) // if your goal is valid, and you have a mitigation goal but no plan for the mitigation goal, then
	{
		m_pBlackboard->SendMessage(m_pMitigationMessage);
	}

	
}

Goal* Manager::GetGoal()
{
	return m_pGoal;
}

void Manager::SetGoal(Goal* pGoal)
{
	m_pGoal = pGoal;

	
}

void Manager::GetNewPlan()
{
	//If you have a goal and the blackboard exists
	if (m_pBlackboard && m_pGoal)
	{
		if(!m_pGoal->UseRiskAnalysis())
		{
			m_pPlanMessage->SetMessage("Plan");
		}
		else if(m_pPlanMessage->GetMessage() != "Ra Plan")
		{
			m_pPlanMessage->SetMessage("Ra Plan");
		}

		//Send the message asking for a new plan
		m_pBlackboard->SendMessage(m_pPlanMessage);
	}

}

unsigned int Manager::GetCurrentAction()
{
	return m_nCurrentAction;
}

void Manager::MessageBlackboard(Message* pMessage)
{
	m_pBlackboard->SendMessage(pMessage);

}

void Manager::ConsiderNewGoal()
{
	m_bNewGoal = true;
}

ActionList& Manager::GetAvailableActions()
{
	return m_apAvailableActions;
}

ActionList& Manager::GetCurrentPlan()
{
	return m_apCurrentPlan;
}

Expectations& Manager::GetExpectations()
{
	return m_pGoal->GetExpectations();
}

Observer* Manager::GetObserver()
{
	return m_pObserver;
}

void Manager::SetMitigation(Goal* pGoal)
{
	m_pMitigation = pGoal;
}

Goal* Manager::GetMitigation()
{
	return m_pMitigation;
}



std::vector<Goal*>& Manager::GetAvailableGoals()
{
	return m_apAvailableGoals;
}

std::unordered_map<std::string, bool>& Manager::GetCurrentWS()
{
	//clear the list of ids
	m_anMessageToID.clear();

	//make sure this goes to the blackboard
	m_anMessageToID.push_back(m_pBlackboard->GetID());

	//Send message to blackboard, asking for the current world state
	m_pBlackboard->SendMessage(m_pCurrentWS);

	//return updated world state
	return m_aCurrentWS;
}

std::unordered_map<std::string, bool>& Manager::GetCurrentWSList()
{
	return m_aCurrentWS;
}
