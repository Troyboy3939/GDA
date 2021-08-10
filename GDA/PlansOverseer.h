#pragma once
#include "Planner.h"

#include "Messenger.h"
#include "MessageBase.h"

class Manager;

class PlansOverseer : public Messenger
{
public:

	//--------------------
	//Constructor/Destructors
	//--------------------
	PlansOverseer(Manager* pManager);
	~PlansOverseer();

	//--------------------
	//Updates the Plansoverseer everyframe
	//--------------------
	void Update(float fDeltaTime);


	//--------------------
	//Constructor/Destructors
	//--------------------
	void HandleMessage(MessageBase* pMessage);

private:
	Planner* m_pPlanner;

};

