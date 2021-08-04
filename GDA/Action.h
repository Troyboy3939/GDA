#pragma once
#include <string>
#include <vector>

class Action
{
public:
	Action();
	~Action();


	float GetCost();
private:

	//list of world states that this action requires
	std::vector<std::string> m_asReqWorldState;

	//world state that this action satisfies
	std::string m_sSatWorldState;


	float m_fCost;

};

