#include "PlansOverseer.h"
#include "Message.h"
#include "Manager.h"
#include "Goal.h"
#include "Expectation.h"
#include "Blackboard.h"
#include "Observer.h"

//													 base class constructor
PlansOverseer::PlansOverseer()  : Messenger(nullptr)
{
	m_pPlanner = new Planner();
}

PlansOverseer::~PlansOverseer()
{
	if(m_pPlanner)
	{
		delete m_pPlanner;
		m_pPlanner = nullptr;
	}


}

void PlansOverseer::Update(float fDeltaTime)
{
}

void PlansOverseer::RiskAnalysis(Manager* pManager)
{
	auto pGoal = pManager->GetGoal();

	auto& rapExpectations = pManager->GetExpectations();

	//Get the point at which a mitigation should be considered
	auto nThreshold = pGoal->GetThreshold();

	//for every expectation that the goal has
	for (auto pExpec : rapExpectations)
	{
		//Perform the Risk Analysis and return the severity 
		auto nSeverity = static_cast<int>(pExpec->RiskAnalysis(pManager));


		//If over the threshold, add mitigation steps to the Manager
		if (nThreshold != RiskSeverity::NONE && nSeverity >= static_cast<int>(nThreshold))
		{
			//get a pointer to the observer
			auto pObserver = pManager->GetObserver();

			//get its explanation map
			auto& explanationMap = pObserver->GetExplanationMap();

			//Get all the explanations that the expectation would have for 
			auto explanations = explanationMap.equal_range(pExpec);
			
			for(auto pIter = explanations.first; pIter != explanations.second; ++pIter)
			{
				auto pResponse = m_pBlackboard->GetResponse(pIter->second,pManager);


				//Set the mitigation if one was found
				if(pResponse)
				{
					pManager->SetMitigation(pResponse);

					//Leave this disgusting mess
					return;
				}
			}
		}
	}
}

void PlansOverseer::SetBlackboard(Blackboard* pBlackboard)
{
	m_pBlackboard = pBlackboard;
}

void PlansOverseer::HandleMessage(Message* pMessage)
{

	auto& rsMessage = pMessage->GetMessage();

	//if the message is to get a plan
	if (rsMessage == "Plan")
	{
		//make sure that the data is a manager
		if (pMessage->GetDataType() == "Manager*")
		{
			//Get a pointer to the manager
			auto pManager = static_cast<Manager*>(pMessage->GetData());


			//Get the plan, passing in the information
			if (m_pPlanner->GetPlan(pManager))
			{
				//exit function, you are done here
				return;
			}


		}
	}
	else if(rsMessage == "RA Plan")
	{
		//make sure that the data is a manager
		if (pMessage->GetDataType() == "Manager*")
		{
			//Get a pointer to the manager
			auto pManager = static_cast<Manager*>(pMessage->GetData());


			RiskAnalysis(pManager);


			//Get the plan, passing in the information
			if (m_pPlanner->GetPlan(pManager))
			{
				//exit function, you are done here
				return;
			}


		}
	}
	
	
}

