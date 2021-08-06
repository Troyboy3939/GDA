#pragma once
#include "Action.h"
#include "Goal.h"
#include <vector>
#include <unordered_map>
class Tree;
class Heap;
class Planner
{
public:

	//----------------------------------------
	//Constructor/Destructors
	//----------------------------------------
	Planner();
	~Planner();

	//----------------------------------------
	//Creates a Plan using Available Actions 
	//----------------------------------------
	void GetPlan(Goal* pGoal, std::vector<Action*>& rapAvailableActions, std::vector<Action*>& raPlan);



private:
	//data structures for finding the plan
	Tree* m_pTree;
	Heap* m_pOpenList;
	std::unordered_map<Action*, bool>* m_pClosedList;
};

