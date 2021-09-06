#include "Planner.h"
#include "Tree.h"
#include "Heap.h"
#include "Manager.h"
#include "Node.h"


Planner::Planner()
{
	//Create a tree
	m_pTree = new Tree();
}

Planner::~Planner()
{
}



	//----------------------------------------
	// Creates a plan and expectations for lists passed in
	//----------------------------------------
bool Planner::GetPlan(Manager* pManager)
{
	//-----------------------------------------------------------------------------------------
	// Set up variables needed for A* / GOAP
	//-----------------------------------------------------------------------------------------


	std::vector<Action*>& rapAvailableActions = pManager->GetAvailableAction();
	std::vector<Action*>& rapPlan = pManager->GetCurrentPlan();
	std::map<std::string, bool>& rExpectedWorldState = pManager->GetExpectedWS();

	//Get a pointer to the goal of the manager
	Goal* pGoal = pManager->GetGoal();



	//Set up the tree
	m_pTree->Clear();
	m_pTree->SetGoal(pGoal);

	//boolean to exit the while loop
	bool bPlanFound = false;

	//prepare data structures (member variables so that they aren't created for every new plan, its quicker to clear them)
	m_pOpenList->Clear();
	m_pClosedList->clear();
	
	//clear the output references
	rExpectedWorldState.clear();
	rapPlan.clear();


	//pointer to the goal node
	Node* pNode = m_pTree->GetGoal();

	

	//the requirement for the goal to be completed
	const std::string& sReq =  pGoal->GetRequiredWorldState();


	//-----------------------------------------------------------------------------------------
	// Add actions that meet the goals requirements
	//-----------------------------------------------------------------------------------------


	//for every available action
	for (int i = 0; i < rapAvailableActions.size(); i++)
	{
		//pointer to the action
		Action* pAction = rapAvailableActions[i];

		//find out what the satisfied world state is
		const std::string& sSat = pAction->GetSatWS();



		//if the required world state of the goal is met by the action, then
		if (sReq.compare(sSat) == 0)
		{
			//Make sure the action is valid  (no point checking a route if the action cannot be undertaken)
			if (pAction->IsValid(pManager))
			{


				Node* pNewNode = new Node(pAction,pNode, pAction->GetReqWS().size());

				//get a reference to the required world 
				std::vector<std::string>& rasParentReqWs = pNode->GetReqWS();

				//Add node to the tree 
				m_pTree->AddNode(pNewNode, pNode);

				//Add it to the open list
				m_pOpenList->Add(pNewNode);

			}
		}
		
	}

	//-----------------------------------------------------------------------------------------
	// Start looking at more actions that meet the added actions requirements, until there are no more requirements left (plan found)
	//-----------------------------------------------------------------------------------------


	
	//while the openlist has something in it
	while (m_pOpenList->Size())
	{
		//Look at the cheapest action currently on the tree
		pNode = m_pOpenList->GetTop();


		//if the node is on the closed list, skip it
		if (m_pClosedList->operator[](pNode))
		{

			continue;
		}


		//if the node has no more required actions, then we've found the path
		if (!pNode->GetReqWS().size())
		{
			bPlanFound = true;
			break;
		}
		

		//add the node to the closed list
		m_pClosedList->insert_or_assign(pNode, true);





		//Get a reference to the required actions
		const std::vector<std::string>& rasParReqLis = pNode->GetReqWS();





		//for every available action
		for (int i = 0; i < rapAvailableActions.size(); i++)
		{
			//pointer to the action
			Action* pAction = rapAvailableActions[i];

			//find out what the satisfied world state is
			const std::string& sSat = pAction->GetSatWS();

			//check every requirement of the node being looked at
			for (int j = 0  ; j < rasParReqLis.size(); j++)
			{

				//get one of the requirements
				const std::string& sReq = rasParReqLis[i];

				const std::map<std::string, bool>& rCurrentWS = pManager->GetCurrentWS();

				//create a copy of the parents requirement list
				std::vector<std::string> asParentReqList = rasParReqLis;

				//if the requirement world state is already met, continue
				if (rCurrentWS[sReq]) //######## fix if this doesn't work
				{
					//#############Could be error if it doesn't exist, make sure to replace
					std::remove(asParentReqList.begin(), asParentReqList.end(), sReq);
					continue;
				}


				//if the action meets the requirement being looked at,
				if (sSat.compare(sReq) == 0)
				{

					//Make sure the action is valid (no point checking a route if the action cannot be undertaken)
					if (pAction->IsValid(pManager))
					{

						


						//erase this requirement off the list of requirements
						for (int k = 0 ; k < asParentReqList.size(); k++)
						{
							if (asParentReqList[k].compare(sSat) == 0)
							{
								asParentReqList.erase(asParentReqList.begin() + k);
							}
						}

						//Create the node
						Node* pNewNode = new Node(pAction,pNode, asParentReqList.size());

						//Add the left over requirements to the child node
						pNewNode->AddReqWS(asParentReqList);

						//Add node to the tree 
						m_pTree->AddNode(pNewNode, pNode);

						//Add it to the open list
						m_pOpenList->Add(pNewNode);
					}
				}
			}

		}


	}



	//-----------------------------------------------------------------------------------------
	// Store the plan inside the reference passed in by working way back up to the goal node
	//-----------------------------------------------------------------------------------------


	//if the path was found
	if (bPlanFound)
	{
		//pointer to the goal node
		Node* pGoal = m_pTree->GetGoal();

	

		//while pNode is not a nullptr or the goal node
		while (pNode != pGoal  && pNode)
		{
			//add the action to the plan
			rapPlan.push_back(pNode->GetAction());


			//set the node to be the parent, work way back up to the goal node
			pNode = pNode->GetParent();

		}


		//-----------------------------------------------------------------------------------------
		// Get the expected world state after the goal has been completed
		//-----------------------------------------------------------------------------------------

		//for every action in the plan
		for (int i = 0; rapPlan.size(); i++)
		{
			if (rapPlan[i])
			{
				//get a reference to the expected effects of the action
				const std::unordered_map<std::string, bool>& rEffects = rapPlan[i]->GetEffects();

				//and append the effects of the action to expected world state
				rExpectedWorldState.insert(rEffects.begin(), rEffects.end());
			}
		}


	
	


		


	}


	//if they both have something in them
	if (rapPlan.size() && rExpectedWorldState.size())
	{
		//then return true
		return true;
	}



	//otherwise, one or both failed, so return false
	return false;

	

}

