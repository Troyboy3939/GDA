#pragma once
#include <unordered_map>
#include "GroupingStructures.h"

class Manager;

class Goal;

class Director
{
public:
	Director(Manager* pManager);

	void PickGoal();



	
	void AddInfluence(Pair<std::string, bool>& rWorldState, Pair<Goal*, float>& rInfluence);

private:

	//------------
	// 	   string: worldstate
	// 	   bool: whether worldstate is true / false
	// 
	// 	   GoalBase*: what the worldstate influences
	// 	   float: how much influence is added to GoalBase*
	//------------
	std::unordered_map<Pair<std::string, bool>&, Pair<Goal*,float>& > m_Influences;

	//Parent
	Manager* m_pManager;

};

