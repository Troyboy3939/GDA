#include "PlansOverseer.h"
#include "Message.h"
#include "Manager.h"
#include "Goal.h"
#include "GoalFormulator.h"
//													 base class constructor
PlansOverseer::PlansOverseer()  : Messenger(nullptr)
{
	m_pPlanner = new Planner();
	m_pGoalFormulator = new GoalFormulator();
}

PlansOverseer::~PlansOverseer()
{
	if(m_pPlanner)
	{
		delete m_pPlanner;
		m_pPlanner = nullptr;
	}

	if (m_pGoalFormulator)
	{
		delete m_pGoalFormulator;
		m_pGoalFormulator = nullptr;
	}
}

void PlansOverseer::Update(float fDeltaTime)
{
}

void PlansOverseer::HandleMessage(Message* pMessage)
{

	auto& rsMessage = pMessage->GetMessage();

	//if the message is to get a plan
	if (rsMessage == "Get Plan")
	{
		//make sure that the data is a manager
		if (pMessage->GetDataType() == "Manager*")
		{
			//Get a pointer to the manager
			auto pManager = static_cast<Manager*>(pMessage->GetData());


			//Get the plan, passing in the information
			if (m_pPlanner->GetPlan(pManager))
			{
				//exit function, you are done here
				return;
			}


		}
	}
	else if(rsMessage == "DeviationsFound")
	{

	}
	
}

