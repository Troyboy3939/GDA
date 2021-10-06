#pragma once
#include <unordered_map>
#include "GroupingStructures.h"
#include <functional>
class Manager;

class Goal;

class Director
{
public:
	//----------------------------------------------------------
	// Initialises Director. nPickingType determines which function
	// is used when picking a goal. 0 = Use influences as percentage
	// 1 = Pick highest influence, x (anything else) = add random value
	// to each, then pick highest
	//----------------------------------------------------------
	Director(Manager* pManager, int nPickingType);

	void PickGoal();



	//Alias Declarations. Make it way easier to read
	using WorldState = Pair<std::string, bool>;
	using Influence = Pair<Goal*, float>;


	void AddInfluence(WorldState& rWorldState, Influence& rInfluence);

	

private:

	//will set the goal of manager to be goal with highest influence
	void PickHighest();

	//same as PickHighest Except it will add random values to each influence
	void PickRandomHighest();

	//Turns values into percentages, and randomly picks a goal
	void PickRandomPercentage();



	//------------
	// 	   string: worldstate
	// 	   bool: whether worldstate is true / false
	// 
	// 	   GoalBase*: what the worldstate influences
	// 	   float: how much influence is added to GoalBase*
	//------------

	
	//hashmap
	std::unordered_map<WorldState&, Influence& > m_aInfluences;

	//used when picking goal, created here so that it isn't created every time
	//its called
	std::unordered_map<Goal*, float> m_aInfluenceAmount;

	//points to which function should be used to pick the goal
	std::function<void()> m_PickFunction;

	//used for PickRandomPercentage()
	float m_fInfluenceTotal;

	//Parent
	Manager* m_pManager;

};

