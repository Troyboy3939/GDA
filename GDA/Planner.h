#pragma once
#include "Action.h"
#include "Goal.h"
#include <vector>
#include <unordered_map>
#include <map>
class Tree;
class Heap;


//----------------------------------------
//The planner class is an object that the plansoverseer will use to 
// make get any plans it might need.
//----------------------------------------
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
	bool GetPlan(Manager* pManager, std::vector<Action*>& rapAvailableActions, std::vector<Action*>& rapPlan, std::map<std::string,bool>& rExpectedWorldState);



private:
	//data structures for finding the plan
	Tree* m_pTree;
	Heap* m_pOpenList;
	std::unordered_map<Node*, bool>* m_pClosedList;
};

