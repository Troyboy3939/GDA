#include "Planner.h"
#include "Tree.h"
#include "Heap.h"
#include <unordered_map>
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

	Heap* pOpenList = new Heap();

	std::unordered_map<Action*, bool>* pClosedList = new std::unordered_map<Action*, bool>;

	Action* pTarget = nullptr;


	//while you haven't found the plan
	while (!bPlanFound)
	{


	}

}

