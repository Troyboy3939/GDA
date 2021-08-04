#pragma once
#include "Action.h"
#include "Goal.h"
#include <vector>

class Tree;

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
	Tree* m_pTree;

};

