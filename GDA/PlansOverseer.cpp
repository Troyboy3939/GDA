#include "PlansOverseer.h"
#include "Message.h"
#include "Manager.h"
#include "Goal.h"
#include <map>
//													 base class constructor
PlansOverseer::PlansOverseer()  : Messenger(nullptr)
{
	m_pPlanner = new Planner();	
}

PlansOverseer::~PlansOverseer()
{
	Messenger::~Messenger();
}

void PlansOverseer::Update(float fDeltaTime)
{
}

void PlansOverseer::HandleMessage(Message* pMessage)
{

	//if the message is to get a plan
	if (pMessage->GetMessage().compare("Get Plan") == 0)
	{
		//make sure that the data is a manager
		if (pMessage->GetDataType().compare("Manager*") == 0)
		{
			//Get a pointer to the manager
			Manager* pManager = (Manager*)pMessage->GetData();


			//Get the plan, passing in the information
			if (m_pPlanner->GetPlan(pManager))
			{
				//exit function, you are done here
				return;
			}


		}
	}
	else //message is for something else
	{

	}
	
}

