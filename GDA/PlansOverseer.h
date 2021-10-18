#pragma once
#include "Planner.h"

#include "Messenger.h"
#include "Message.h"


class GoalFormulator;
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
	void HandleMessage(Message* pMessage) override;


	//Components of plans overseer
	Planner* m_pPlanner;
	GoalFormulator* m_pGoalFormulator;
};

