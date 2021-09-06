#include "Messenger.h"
#include "Message.h"

Messenger::Messenger(Blackboard* pBlackboard)
{
	//Setup ID
	m_nID = m_nNetworkSize;
	m_nNetworkSize++;

	m_pBlackboard = pBlackboard;

}

bool Messenger::SendMessage(Message* pMessage)
{
	//if the message and next person exist
	if (pMessage)
	{	
		//if this message isn't meant for you
		if (pMessage->CheckID(m_nID))
		{
			//message is meant for us
			HandleMessage(pMessage);

			return true;
		}

	}
		return false;

}

unsigned int Messenger::GetID()
{
	return m_nID;
}

