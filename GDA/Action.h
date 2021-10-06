#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


class Manager;

using WorldStateList = std::vector<std::string>;


class Action
{
public:
	Action(float fCost, std::function<bool(Manager* pManager)>* pIsValidFuction, std::string& rsType,void* pData = nullptr);

	virtual ~Action() = default;



	//------------------------------------
	// Returns the cost of performing this action
	//------------------------------------
	float GetCost();

	//------------------------------------
	// Returns the world state that this action satisfies
	//------------------------------------
	std::string& GetSatWS();


	//------------------------------------
	// Returns the WS that this action requires in order for it to be able to be done
	//------------------------------------
	WorldStateList& GetReqWS();

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
	std::string& GetDataType();

	//------------------------------------
	// Sets data
	//------------------------------------
	void SetData(void* pData);

	//------------------------------------
	// Updates the type of data
	//------------------------------------
	void SetDataType(std::string& rsType);
protected:
	

	//list of world states that this action requires
	WorldStateList m_asReqWorldState;

	//world state that this action satisfies
	std::string m_sSatWorldState;

	//cost of performing this action
	float m_fCost;

	//function pointer to check whether the action can be completed or not
	std::function<bool(Manager* pManager)>* m_pIsValid;

	//Data included with the action
	void* m_pData;

	//type of m_pData
	std::string m_sDataType;

};

