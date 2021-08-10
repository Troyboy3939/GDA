#include "Messenger.h"
#include "MessageBase.h"

Messenger::Messenger()
{
	//Setup ID
	m_nID = m_nNetworkSize;
	m_nNetworkSize++;
}

void Messenger::SendMessage(MessageBase* pMessage)
{
	//if the message and next person exist
	if (pMessage && m_pNext)
	{


		//if you haven't already checked this message
		if (pMessage->CheckPassThrough(m_nID))
		{
			//if this message isn't meant for you
			if (pMessage->CheckID(m_nID))
			{
				//Pass it through the network
				m_pNext->SendMessage(pMessage);

				return;
			}

			//otherwise, the message is intended for you, so
			HandleMessage(pMessage);
		}

	}

}

void Messenger::SetNextMessenger(Messenger* pNext)
{
	m_pNext = pNext;
}

