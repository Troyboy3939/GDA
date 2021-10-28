#include "Blackboard.h"
#include "PlansOverseer.h"
#include "Message.h"
#include "GroupingStructures.h"
#include "BlackboardData.h"
#include "Manager.h"

//----------------------
// Constructor, Plans Overseer
// Must be created first, then Blackboard
//----------------------
Blackboard::Blackboard(PlansOverseer* pOverseer) : Messenger(nullptr)
{
	m_pPlansOverseer = pOverseer;
}


//----------------------
// Destructor, should 
// delete all data added to it
//----------------------
Blackboard::~Blackboard()
{
	//Delete all entries to m_apData
}


//----------------------
// Update Function, called
// every frame, pass in deltaTime,
// which represents the time between
// frames
//----------------------
void Blackboard::Update(float fDeltaTime)
{
}


//----------------------
// Called if a message is sent
// to the it. Will pass on appropiate
// messages. Messages intended for it,
// will be handled in a seperate function
//----------------------
bool Blackboard::SendMessage(Message* pMessage)
{
	if (pMessage)
	{
		//if message isn't intended for us, then
		if (!Messenger::SendMessage(pMessage) && m_pPlansOverseer)
		{
			//Check if it is intended for the plans overseer
			if(pMessage->CheckID(m_pPlansOverseer->GetID()))
			{
				//Pass it to the overseer
				return m_pPlansOverseer->SendMessage(pMessage);
			}
		}
	}
	

	return false;
}

//----------------------
// Interprets what the message is for
// When a message is intended for it,
// a string will be split, the first is
// the command, such as Add or World State,
// the second is the name of what ever the command is
//----------------------
void Blackboard::HandleMessage(Message* pMessage)
{
	//if message exists
	if (pMessage)
	{
		//Get the message
		const auto& rsMessage = pMessage->GetMessage();

		/*
			Messages are split as such

			Command: Value
		
			Examples:

			Add: PlayerPosition --> this will add whatever data is attached onto the data map, with the key of "PlayerPosition"
			WorldState: HasWeapon --> this will set the world state of "HasWeapon" to what data is attached (which should be a boolean)
		*/



		//if the message is to add, and the message is longer than what is compared (meaning its "Add: _____", where _ is a word)
		if (rsMessage.compare("Add: ") < 0)
		{
			//Get the key for what they want to add
			std::string sKey;
			GetSubString(rsMessage,sKey);

			//Create a new data pointer
			auto pValue = new BlackboardData(pMessage->GetData(),pMessage->GetDataType());

			//insert data into map
			m_apData.insert_or_assign(sKey,pValue);

		} //if the message is to update a worldstate, and sMessage is longer, 
		else if (rsMessage.compare("WorldState: ") < 0)
		{
			//Get the string for the world state they want to update
			std::string sWorldState;
			GetSubString(rsMessage,sWorldState);

			//Make sure the data type is bool, 
			if (pMessage->GetDataType() == "bool")
			{
				//Add or update the world state that is sKey, with the value of pMessage->m_pData
				m_aWorldState.insert_or_assign(sWorldState,static_cast<bool>(pMessage->GetData()));
			}
		}
		else if(rsMessage == "Deviations Found")
		{
			if(pMessage->GetDataType() == "Manager*" )
			{
				//Get pointer to manager
				auto pManager = static_cast<Manager*>(pMessage->GetData());

				//Formulate some goals
				GoalFormulator(pManager);
			}
		}
	}
}

void Blackboard::GoalFormulator(Manager* pManager)
{

	//Get the current explanations for the deviations
	auto& arsExplanations = pManager->GetExplanations();

	//for every explanation
	for(auto& rExpl : arsExplanations)
	{

		auto responses = m_Reponses.equal_range(rExpl);


		//go through every response the explanation will have
		for(auto pIt = responses.first; pIt != responses.second; pIt++)
		{
			//Get the data which is stored inside the value of map -> first is manager, second is the goal

			auto pManager = static_cast<Manager*>(pIt->second.first);

			auto pGoal = static_cast<Goal*>(pIt->second.second);

			//Get a reference to the available goals of pManager, then add the goal to the manager
			pManager->GetAvailableGoals().push_back(pGoal);

			//Tell the manager to consider getting a new goal
			pManager->ConsiderNewGoal();
		}

	}


}


//----------------------
// Since managers require a 
// Blackboard, they have to added
// after this is created,
// so that adds the managers onto a dynamic
// array
//----------------------
void Blackboard::AddManager(Manager* pManager)
{
	m_apManagers.push_back(pManager);
}


//----------------------
// returns the data that 
// is associated with the
// key 'rsKey'. 
//----------------------
BlackboardData* Blackboard::GetValue(std::string& rsKey)
{
	auto pIterator = m_apData.find(rsKey);

	if(pIterator != m_apData.end())
	{
		return pIterator->second;
	}

	return nullptr;
}

void Blackboard::AddResponse(std::string& rsExplanation, Response response)
{
	m_Reponses.emplace(rsExplanation,response);
}

Goal* Blackboard::GetResponse(std::string& rsExplanation, Manager* pManager)
{
	auto resp = m_Reponses.equal_range(rsExplanation);

	for (auto pIt = resp.first; pIt != resp.second; pIt++)
	{
		if(pIt->second.first == pManager)
		{
			return pIt->second.second;
		}
	}


	return nullptr;
}




//----------------------
// Seperates a command 
// from the value, returns
// the value and removes the 
// space inbetween
//----------------------
void Blackboard::GetSubString(const std::string& rsString, std::string& rsKey)
{
	
		// find the position of the space(shown in the compare above)
		auto nPos = rsString.find(" ");

		//create a new string from (including) space to end of string
		rsKey = rsString.substr(nPos);

		//remove the space from the key
		rsKey.erase(0);
}
