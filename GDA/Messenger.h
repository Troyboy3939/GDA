#pragma once


//----------------------------------------
// Abstract class so that different classes 
// can communicate with each other
// this is the oberver design pattern
//----------------------------------------

class MessageBase;


class Messenger
{
public:
	Messenger(Messenger* pNext);
	virtual ~Messenger() = 0;

	virtual void Update(float fDeltaTime) = 0;

	//function that determines whether the message is intended for this messenger
	virtual void SendMessage(MessageBase* pMessage);


	void SetNextMessenger(Messenger* pNext);

protected:
	//pure virtual function for handling messages
	virtual void HandleMessage(MessageBase* pMessage) = 0;

	//Id of this messenger
	unsigned int m_nID;

	//next person in messenger network
	Messenger* m_pNext;

	//number of people in the network
	static int m_nNetworkSize;

};

//initialise the static int
int Messenger::m_nNetworkSize = 0;
