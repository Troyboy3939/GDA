#pragma once
#include <vector>
#include <unordered_map>
#include <map>

class Tree;
class Heap;
class Goal;
class Node;
class Action;
class Manager;
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
	bool GetPlan(Manager* pManager);



private:
	//data structures for finding the plan
	Tree* m_pTree;
	Heap* m_pOpenList;
	std::unordered_map<Node*, bool>* m_pClosedList;
};

