#include "PlansOverseer.h"
#include "Message.h"
#include "Manager.h"
#include "Goal.h"

//													 base class constructor
PlansOverseer::PlansOverseer(Manager* pManager)  : Messenger()
{
	//Set the Manager passed in as the next messenger in the observer pattern network
	SetNextMessenger((Messenger*)pManager);
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

	
}

