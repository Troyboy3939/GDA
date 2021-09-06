#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


class Manager;

class Action
{
public:
	Action(float fCost, std::function<bool(Manager* pManager)>* pIsValidFuction, void* pData = nullptr, std::string sType = "");

	virtual ~Action();



	//------------------------------------
	// Returns the cost of performing this action
	//------------------------------------
	float GetCost();

	//------------------------------------
	// Returns the world state that this action satisfies
	//------------------------------------
	std::string GetSatWS();


	//------------------------------------
	// Returns the WS that this action requires in order for it to be able to be done
	//------------------------------------
	std::vector<std::string> GetReqWS();


	//------------------------------------
	// Adds an effect of doing performing this action
	//------------------------------------
	void AddEffect(std::string sWS, bool bValue);


	//------------------------------------
	// Returns the list of how the action affects the worlds state
	//------------------------------------
	std::unordered_map<std::string, bool> GetEffects();


	//------------------------------------
	// Calls the function pointer. Determines
	// whether an action can be completed 
	// or not
	//------------------------------------
	virtual bool IsValid(Manager* pManager);

	//------------------------------------
	// returns the data passed in
	//------------------------------------
	void* GetData();

	//------------------------------------
	// returns the type of m_pData
	//------------------------------------
	std::string GetDataType();

	//------------------------------------
	// Sets data
	//------------------------------------
	void SetData(void* pData);

	//------------------------------------
	// Updates the type of data
	//------------------------------------
	void SetDataType(std::string sType);
protected:
	

	//list of world states that this action requires
	std::vector<std::string> m_asReqWorldState;

	//world state that this action satisfies
	std::string m_sSatWorldState;

	//map that stores the effects that this action will have
	std::unordered_map<std::string, bool> m_Effects;

	//cost of performing this action
	float m_fCost;

	//function pointer to check whether the action can be completed or not
	std::function<bool(Manager* pManager)>* m_pIsValid;

	//Data included with the action
	void* m_pData;

	//type of m_pData
	std::string m_sDataType;

};

