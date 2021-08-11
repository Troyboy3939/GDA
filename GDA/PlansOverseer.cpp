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

void PlansOverseer::HandleMessage(MessageBase* pMessage)
{

	//if the message is to get a plan
	if (pMessage->GetMessage().compare("Get Plan") == 0)
	{
		//convert the Message to the appropriate type so that the information can be extracted
		auto pMes = (Message<Quad<Manager*, std::vector<ActionBase*>&, std::vector<ActionBase*>&, std::map<std::string,bool>&>>*)pMessage;

		auto pData = pMes->GetData();

		//extract the data from the message
		Manager* pManager = pData->m_Data1;
		std::vector<ActionBase*>& rPlan = pData->m_Data2;
		std::vector<ActionBase*>& rAvailableAction = pData->m_Data3;
		std::map<std::string, bool>& aWS = pData->m_Data4;

		//Get the plan, passing in the information
		if (m_pPlanner->GetPlan(pManager, rAvailableAction, rPlan, aWS))
		{
			//exit function, you are done here
			return;
		}
		


	}
	
}

