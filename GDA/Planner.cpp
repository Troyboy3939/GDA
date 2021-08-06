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
	// Creates a plan for the array passed in 
	//----------------------------------------
void Planner::GetPlan(Goal* pGoal, std::vector<Action*>& rapAvailableActions, std::vector<Action*>& rapPlan)
{
	//Set up the tree
	m_pTree->Clear();
	m_pTree->SetGoal(pGoal);

	
	bool bPlanFound = false;

	//prepare data structures (member variables so that they aren't created for every new plan, its quicker to clear them)
	m_pOpenList->Clear();
	m_pClosedList->clear();
	

	//pointer to the goal node
	Node* pNode = m_pTree->GetGoal();

	//TODO ADD GOAL AND ACTIONS TO THE CLOSED LIST
	//m_pClosedList->insert(pNode,);

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

		//TODO ADD NODE TO THE CLOSED LIST

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


					
					//Add node to the tree 
					m_pTree->AddNode(pNewNode, pNode);

					//Add it to the open list
					m_pOpenList->Add(pNewNode);
				}
			}
			

			


		}


	}

	

}

