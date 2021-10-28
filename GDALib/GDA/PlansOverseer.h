#pragma once
#include "Planner.h"

#include "Messenger.h"
#include "Message.h"

class Manager;


class PlansOverseer : public Messenger
{
public:
	enum class RiskSeverity
	{
		LOW,
		MEDIUM,
		HIGH,
		EXTREME,
		NONE
	};


	//--------------------
	//Constructor/Destructors
	//--------------------
	PlansOverseer();
	~PlansOverseer();

	//--------------------
	//Updates the Plansoverseer everyframe
	//--------------------
	void Update(float fDeltaTime);


	//--------------------
	// Gives pManager a Mitigation
	// Goal for it to complete
	// WARNING COULD BE VERY SLOW
	// KEEP PLANS MINIMAL
	//--------------------
	void RiskAnalysis(Manager* pManager);


private:

	//--------------------
	//Constructor/Destructors
	//--------------------
	void HandleMessage(Message* pMessage) override;




	//Components of plans overseer
	Planner* m_pPlanner;
};

