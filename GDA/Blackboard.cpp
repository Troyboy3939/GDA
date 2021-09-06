#include "Blackboard.h"
#include "PlansOverseer.h"
#include "Message.h"

Blackboard::Blackboard(PlansOverseer* pOverseer) : Messenger(nullptr)
{
	m_pPlansOverseer = pOverseer;
}

void Blackboard::Update(float fDeltaTime)
{
}

bool Blackboard::SendMessage(Message* pMessage)
{
	if (pMessage)
	{
		//if message isn't intended for us, then
		if (!Messenger::SendMessage(pMessage) && m_pPlansOverseer)
		{
			//Check if it is intended for the plans overseer
			if(pMessage->CheckID(m_pPlansOverseer->GetID()))
			{
				//Pass it to the overseer
				m_pPlansOverseer->SendMessage(pMessage);
			}
		}
	}
	
}

void Blackboard::HandleMessage(Message* pMessage)
{

}



void Blackboard::AddManager(Manager* pManager)
{
	m_apManagers.push_back(pManager);
}
