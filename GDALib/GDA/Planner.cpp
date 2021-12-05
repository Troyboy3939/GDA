#include "Planner.h"
#include "Tree.h"
#include "Heap.h"
#include "Manager.h"
#include "Node.h"
#include "Action.h"

Planner::Planner()
{
	//Create a tree
	m_pTree = new Tree();

	m_pOpenList = new Heap();

	m_pNodePool = new NodePool();
}

Planner::~Planner()
{
	if (m_pTree)
	{
		delete m_pTree;
		m_pTree = nullptr;
	}

	if (m_pOpenList)
	{
		delete m_pOpenList;
		m_pOpenList = nullptr;
	}

	if (m_pNodePool)
	{
		delete m_pNodePool;
		m_pNodePool = nullptr;
	}

}



	//----------------------------------------
	// Creates a plan and expectations for lists passed in
	//----------------------------------------
bool Planner::GetPlan(Manager* pManager)
{
	//-----------------------------------------------------------------------------------------
	// Set up variables needed for A* / GOAP
	//-----------------------------------------------------------------------------------------

	//list of available actions
	auto& rapAvailableActions = pManager->GetAvailableActions();

	//reference to the current plan
	auto& rapPlan = pManager->GetCurrentPlan();

	//reference to the expected world state
	auto& rExpectedWorldState = pManager->GetExpectations();

	//Get a pointer to the goal of the manager
	auto pGoal = pManager->GetGoal();



	//Set up the tree
	m_pTree->Clear(m_pNodePool);
	m_pTree->SetGoal(pGoal);

	//boolean to exit the while loop
	auto bPlanFound = false;

	//prepare data structures (member variables so that they aren't created for every new plan, its quicker to clear them)
	m_pOpenList->Clear();
	m_ClosedList.clear();
	
	//clear the output references
	rExpectedWorldState.clear();
	rapPlan.clear();


	//pointer to the goal node
	auto pNode = m_pTree->GetGoal();

	

	//the requirement for the goal to be completed
	const auto& sReq =  pGoal->GetRequiredWorldState();


	//-----------------------------------------------------------------------------------------
	// Add actions that meet the goals requirements
	//-----------------------------------------------------------------------------------------


	//for every available action
	for (int i = 0; i < rapAvailableActions.size(); i++)
	{
		//pointer to the action
		auto pAction = rapAvailableActions[i];

		//find out what the satisfied world state is
		const auto& sSat = pAction->GetSatWS();



		//if the required world state of the goal is met by the action, then
		if (sReq == sSat)
		{
			//Make sure the action is valid  (no point checking a route if the action cannot be undertaken)
			if (pAction->IsValid(pManager))
			{


				auto pNewNode = m_pNodePool->GetNode();
				pNewNode->Initialise(pAction,pNode, static_cast<float>(pAction->GetReqWS().size()));

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

	//Get a reference to the current world state
	auto& rCurrentWS = pManager->GetCurrentWS();
	
	auto bExit = false;


	//while the openlist has something in it
	while (m_pOpenList->Size())
	{
		

		//Look at the cheapest action currently on the tree
		pNode = m_pOpenList->GetTop();


		//if the node is on the closed list, skip it
		if (m_ClosedList[pNode])
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
		m_ClosedList[pNode] = true;





		//Get a reference to the array of world states required by its parent
		auto& rasParentRequirements = pNode->GetReqWS();

		auto& raCurrentWS = pManager->GetCurrentWS();


		//unfornutately needed for every requirement
		//auto asActionRequirementsLeft = rasParentRequirements;

	
		//for every available action check if this action satifies the requirement of its potential parent and then add it to the tree if it does
		for (int i = 0; i < rapAvailableActions.size(); i++)
		{
			auto bReturn = true;


			auto pNewNode = m_pNodePool->GetNode();
			

			auto rapReqList = pNewNode->GetReqWS();
			rapReqList.clear();

			//insert parents requirements onto this
			rapReqList.insert(rapReqList.end(), rasParentRequirements.begin(), rasParentRequirements.end());

			//pointer to the action
			auto pAction = rapAvailableActions[i];


			//Make sure the action is valid (no point checking a route if the action cannot be undertaken)
			if (!pAction->IsValid(pManager))
			{
				continue;
			}



			//find out what the satisfied world state is
			const auto& sSat = pAction->GetSatWS();


			for (int j = 0; j < rasParentRequirements.size(); j++)
				//check every requirement of the node being looked at
			{


				//-----------------------------------
				// Set up appropriate variables
				//-----------------------------------

				//create a copy of the parents requirement list


				//get one of the requirements
				auto& sReq = rasParentRequirements[j];






				//-----------------------------------
				// Check if the requirement is already met
				//-----------------------------------

				//see if the parents requirement is already met
				auto iter = rCurrentWS.find(sReq);

				//if the world state requirement of parent exists, then we need to check if its true
				if (iter != rCurrentWS.end())
				{
					//if the world state is true, then there
					if (iter->second)
					{
						//if the required world state is already met, continue
						auto it = std::remove(rapReqList.begin(), rapReqList.end(), iter->first);

						rapReqList.erase(it, rapReqList.end());

						if (rapReqList.empty())
						{

							//Create the node
							pNewNode->Initialise(pAction, pNode, static_cast<float>(rapReqList.size()));

							pNewNode->AddReqWS(rapReqList);

							//Add node to the tree
							m_pTree->AddNode(pNewNode, pNode);

							//Add it to the open list
							m_pOpenList->Add(pNewNode);

							pNode = pNewNode;

							bPlanFound = true;
						
							bExit = true;
						}


						continue;
					}
				}



				//if the action meets the requirement being looked at,
				if (sSat == sReq)
				{
					//erase this requirement off the list of requirements
					for (int k = 0; k < rapReqList.size(); k++)
					{
						if (rapReqList[k] == sSat)
						{
							rapReqList.erase(rapReqList.begin() + k);
						}
					}

					//Create the node
					pNewNode->Initialise(pAction, pNode, static_cast<float>(rapReqList.size()));

					pNewNode->AddReqWS(rapReqList);

					//Add node to the tree
					m_pTree->AddNode(pNewNode, pNode);

					//Add it to the open list
					m_pOpenList->Add(pNewNode);

					bReturn = false;

				}
				if (bExit)
				{
					break;
				}
			}

			if (bExit)
			{
				break;
			}

			if (bReturn)
			{
				m_pNodePool->Return(pNewNode);
			}
		}

		if (bExit)
		{
			break;
		}
		
	}



	//-----------------------------------------------------------------------------------------
	// Store the plan inside the reference passed in by working way back up to the goal node
	//-----------------------------------------------------------------------------------------


	//if the path was found
	if (bPlanFound)
	{
		//pointer to the goal node
		auto pGoal = m_pTree->GetGoal();

	

		//while pNode is not a nullptr or the goal node
		while (pGoal && pNode && pNode != pGoal)
		{
			//add the action to the plan
			rapPlan.push_back(pNode->GetAction());


			//set the node to be the parent, work way back up to the goal node
			pNode = pNode->GetParent();

		}
	}
		//then return true
		return !rapPlan.empty();
}

/*
*
* 
		//for every requirement
		for (auto& rsReq : rasParentRequirements)
		{
			if (rsReq == "")
			{
				continue;
			}

			//see if the parents requirement is already met
			auto iter = rCurrentWS.find(rsReq);

			//if the world state requirement of parent exists, then we need to check if its true
			if (iter != rCurrentWS.end())
			{
				//if the world state is true, then there
				if (iter->second)
				{
					//if the required world state is already met, continue
					auto it = std::remove(asActionRequirementsLeft.begin(), asActionRequirementsLeft.end(), iter->first);

					asActionRequirementsLeft.erase(it, asActionRequirementsLeft.end());

					if (asActionRequirementsLeft.empty())
					{
						bPlanFound = true;
						bExit = true;
						break;
					}
					continue;
				}
			}

			

			//for every available action
			for (auto pAction : rapAvailableActions)
			{

				//Make sure the action is valid (no point checking a route if the action cannot be undertaken)
				if (!pAction->IsValid(pManager))
				{
					continue;
				}



				auto& rsSat = pAction->GetSatWS();

				if (rsSat == rsReq)
				{
					//erase this requirement off the list of requirements
					for (int k = 0; k < asActionRequirementsLeft.size(); k++)
					{
						if (asActionRequirementsLeft[k] == rsSat)
						{
							asActionRequirementsLeft.erase(asActionRequirementsLeft.begin() + k);
						}
					}

					//Create the node
					auto pNewNode = m_pNodePool->GetNode();
					pNewNode->Initialise(pAction, pNode, static_cast<float>(asActionRequirementsLeft.size()));


					//Add the left over requirements to the child node
					pNewNode->AddReqWS(asActionRequirementsLeft);
					

					//Add node to the tree 
					m_pTree->AddNode(pNewNode, pNode);

					//Add it to the open list
					m_pOpenList->Add(pNewNode);
				}
			}
		}
		
		if (bExit)
		{
			break;
		}
		


*/