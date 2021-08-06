#pragma once
#include <string>
#include <vector>

class Action
{
public:
	Action();
	~Action();


	float GetCost();

	//------------------------------------
	// Returns the world state that this action satisfies
	//------------------------------------
	std::string GetSatWS();


	//------------------------------------
	// Returns the WS that this action requires in order for it to be able to be done
	//------------------------------------
	std::vector<std::string> GetReqWS();
private:

	//list of world states that this action requires
	std::vector<std::string> m_asReqWorldState;

	//world state that this action satisfies
	std::string m_sSatWorldState;


	float m_fCost;

};

