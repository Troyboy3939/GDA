#include "Director.h"
#include <map>
#include <string>
#include "Manager.h"
#include <algorithm>
#include "Goal.h"
Director::Director(Manager* pManager)
{
	m_pManager = pManager;
}

void Director::PickGoal()
{
	//Get the current world state from the observer / manager
	std::map<std::string, bool>& rCurrentWS = m_pManager->GetCurrentWS();

	//get a reference of the list of current goals
	std::vector<GoalBase*> apAvailableGoals = m_pManager->GetAvailableGoals();

	//Create a map that takes in a goal as a key and returns its value
	std::map<GoalBase*, float> aGoalInfluenceAmount;

	
	//for every world state in rCurrent World State
	for (auto const& rWorldState : rCurrentWS)
	{

		//convert std::pair to custom pair
		auto ws = Pair<std::string, bool>(rWorldState.first, rWorldState.second);

		//##################TODO REPLACE WITH OWN MAP THIS WILL BE AN ERROR WHEN NOTHING IS FOUND####################################
		auto influence = m_Influences.at(ws);


		//if statement here checking if influence is null



		//for every available goal
		for (int i = 0; i < apAvailableGoals.size(); i++)
		{
			//Get a pointer to the goal that is influenced by the world state
			GoalBase* pGoal = influence.m_Data1;

			//if this goal is in fact 
			if (pGoal == apAvailableGoals[i])
			{
				//Add the amount of influence to the map
				//if the goal isn't on the map, its created with a default of 0, so this is actually fine
				aGoalInfluenceAmount[pGoal] += influence.m_Data2;
			}
		}

	}

	//find the goal with the most influence
	GoalBase* pGoal = std::max_element(aGoalInfluenceAmount.begin(),aGoalInfluenceAmount.end())._Ptr->_Myval.first;

	//Set the goal
	m_pManager->SetGoal(pGoal);

}

void Director::AddInfluence(Pair<std::string, bool>& rWorldState, Pair<GoalBase*, float>& rInfluence)
{
	m_Influences.insert_or_assign(rWorldState, rInfluence);
}

