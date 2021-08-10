#include "Planner.h"
#include "Tree.h"
#include "Heap.h"

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
bool Planner::GetPlan(Goal* pGoal, std::vector<Action*>& rapAvailableActions, std::vector<Action*>& rapPlan, std::map<std::string, bool>& rExpectedWorldState)
{
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
			Node* pNewNode = new Node();

			//get a reference to the required world states
			const std::vector<std::string>& rasReqWS = pAction->GetReqWS();



			//create a copy of the world states so that world states can be added to the node if needed (without affecting the action)
			pNewNode->SetReqWS(rasReqWS);

			//Setup A* scores


			//G score is simply the cost of the action 
			pNewNode->SetGScore(pAction->GetCost());

			//THe hueristic is simply the number of left over world states
			pNewNode->SetHScore(rasReqWS.size());

			//Add node to the tree 
			m_pTree->AddNode(pNewNode, pNode);

			//Add it to the open list
			m_pOpenList->Add(pNewNode);
			

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
		const std::vector<std::string>& asReqLis = pNode->GetReqWS();





		//for every available action
		for (int i = 0; i < rapAvailableActions.size(); i++)
		{
			//pointer to the action
			Action* pAction = rapAvailableActions[i];

			//find out what the satisfied world state is
			const std::string& sSat = pAction->GetSatWS();

			//check every requirement of the node being looked at
			for (int j = 0  ; j < asReqLis.size(); j++)
			{



				//get one of the requirements
				const std::string& sReq = asReqLis[i];

				//if the action meets the requirement being looked at,
				if (sSat.compare(sReq) == 0)
				{
					Node* pNewNode = new Node();

					//get a reference to the required world states of the soon to be child
					const std::vector<std::string>& rasReqWS = pAction->GetReqWS();



					//create a copy of the world states so that world states can be added to the node if needed (without affecting the action)
					pNewNode->SetReqWS(rasReqWS);

					//for every requirement the current node has.
					for (int k = 0; k < asReqLis.size(); k++)
					{

						//make sure its a different world state (.compare == 0 means true)
						if (asReqLis[i].compare(sSat))
						{
							//Add required world state from current node to child node
							pNewNode->AddReqWS(asReqLis[i]);
						}

					}

					//Setup A* scores

					

					//G score is simply the cost of the action 
					pNewNode->SetGScore(pAction->GetCost());

					//The hueristic is simply the number of left over world states
					pNewNode->SetHScore(pNewNode->GetReqWS().size());

					//F score isn't needed to be setup, since its literally G + H. 
					
					//Add node to the tree 
					m_pTree->AddNode(pNewNode, pNode);

					//Add it to the open list
					m_pOpenList->Add(pNewNode);
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
				const std::map<std::string, bool>& rEffects = rapPlan[i]->GetEffects();

				//and append the effects of the action to expected world state
				rExpectedWorldState.insert(rEffects.begin(), rEffects.end());
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




	

}

