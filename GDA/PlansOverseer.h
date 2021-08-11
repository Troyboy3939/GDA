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
	PlansOverseer();
	~PlansOverseer();

	//--------------------
	//Updates the Plansoverseer everyframe
	//--------------------
	void Update(float fDeltaTime);



private:

	//--------------------
	//Constructor/Destructors
	//--------------------
	void HandleMessage(MessageBase* pMessage);

	Planner* m_pPlanner;

};

