#include "Messenger.h"
#include "Message.h"

//initialise the static int
int Messenger::m_nNetworkSize = 0;

Messenger::Messenger(Blackboard* pBlackboard)
{
	//Setup ID
	m_nID = m_nNetworkSize;
	m_nNetworkSize++;

	m_pBlackboard = pBlackboard;

}

Messenger::~Messenger()
{
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

