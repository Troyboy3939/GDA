#include "Director.h"
#include <map>
#include <string>
#include "Manager.h"
#include <algorithm>
#include <random>
#include <ctime>


Director::Director(Manager* pManager, int nPickingType)
{
	m_pManager = pManager;

	srand(time(0));

	m_fInfluenceTotal = 0;


	//Determine which function should used
	if(nPickingType == 0)
	{
		m_PickFunction = [=]() {PickRandomPercentage(); };
		
	}
	else if(nPickingType == 1)
	{
		m_PickFunction = [=]() {PickHighest(); };
	}
	else
	{
		m_PickFunction = [=]() {PickRandomHighest(); };
	}

}

void Director::PickGoal()
{
	//Get the current world state from the observer / manager
	auto& raCurrentWS = m_pManager->GetCurrentWS();

	//get a reference of the list of current goals
	auto& rapAvailableGoals = m_pManager->GetAvailableGoals();

	//clear the map
	m_aInfluenceAmount.clear();

	m_fInfluenceTotal = 0.0f;

	
	//for every world state in rCurrent World State
	for (auto const& rWorldState : raCurrentWS)
	{

		//convert std::pair to custom pair
		auto ws = WorldState(rWorldState.first, rWorldState.second);

		//get an iterator to the ws/influence if it exists
		auto influenceIter = m_aInfluences.find(ws);

		//if it exists
		if (influenceIter != m_aInfluences.end())
		{

			//Get a reference to the influence
			auto& influence = influenceIter->second;

			//for every available goal
			for (int i = 0; i < rapAvailableGoals.size(); i++)
			{
				//Get a pointer to the goal that is influenced by the world state
				auto pGoal = influence.m_Data1;

				//if this goal is in fact 
				if (pGoal == rapAvailableGoals[i])
				{
					//Add the amount of influence to the map
					//if the goal isn't on the map, its created with a default of 0, so this is actually fine
					m_aInfluenceAmount[pGoal] += influence.m_Data2;
					m_fInfluenceTotal += influence.m_Data2;

				}
			}
		}

	}


	if(m_PickFunction)
	{
		m_PickFunction();
	}



}

void Director::AddInfluence(WorldState& rWorldState, Influence& rInfluence)
{
	m_aInfluences.insert_or_assign(rWorldState, rInfluence);
}

void Director::PickRandomPercentage()
{

	//random value between 0 - maximum amount of influence
	auto fRandomValue = static_cast <float> (rand()) / (RAND_MAX / (m_fInfluenceTotal));

	
	for(auto& it : m_aInfluenceAmount)
	{

		fRandomValue -= it.second;

		if (fRandomValue <= 0.0f)
		{
			m_pManager->SetGoal(it.first);
			return;
		}
	}
}

void Director::PickHighest()
{
	//find the goal with the most influence
	auto pGoal = std::max_element(m_aInfluenceAmount.begin(), m_aInfluenceAmount.end())._Ptr->_Myval.first;

	//Set the goal
	m_pManager->SetGoal(pGoal);
}

void Director::PickRandomHighest()
{
	//get how many influences there are
	const auto nSize = m_aInfluenceAmount.size();

	//Calculate average influence amount
	const auto fAverageInfluence = m_fInfluenceTotal / nSize;

	//minumum value to add
	const auto fMinimum = fAverageInfluence - fAverageInfluence * 0.5f;

	//maximum value to add
	const auto fMaximum = fAverageInfluence + fAverageInfluence * 0.5f;



	//for every influence
	for(auto& it: m_aInfluenceAmount)
	{
		it.second += fMinimum + static_cast <float> (rand()) / (RAND_MAX / (fMaximum - fMinimum));
	}

	//Pick Highest value
	PickHighest();


}