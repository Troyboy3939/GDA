#pragma once


//----------------------------------------
// Abstract class so that different classes 
// can communicate with each other
// this is the oberver design pattern
//----------------------------------------

class Message;
class Blackboard;

class Messenger
{
public:
	//---------------------
	// Constructors / Destructors
	//---------------------	

	Messenger(Blackboard* pBlackboard);
	virtual ~Messenger() = 0;

	//---------------------
	// Called every frame
	//---------------------
	virtual void Update(float fDeltaTime) = 0;

	//---------------------
	// return true if message is being handled, is called when a message is being sent to this messenger
	//---------------------
	virtual bool SendMessage(Message* pMessage);

	//---------------------
	// Returns the ID of the messenger
	//---------------------	
	unsigned int GetID();

protected:
	//pure virtual function for handling messages
	virtual void HandleMessage(Message* pMessage) = 0;

	//Id of this messenger
	unsigned int m_nID;

	//pointer to the blackboard
	Blackboard* m_pBlackboard;

	//number of people in the network
	static int m_nNetworkSize;

};

//initialise the static int
int Messenger::m_nNetworkSize = 0;
