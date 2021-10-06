#include "Observer.h"
#include "Manager.h"
#include "Action.h"


//-------------------------------------------------------------------------------------------------------------
// Public Functions
//-------------------------------------------------------------------------------------------------------------

Observer::Observer(Manager* pManager)
{
    m_pManager = pManager;
    m_aExpectedWorldState = pManager->GetExpectedWS();

    m_bWSUpdated = false;
    m_nCurrentAction = 0;

}

WorldStateMap& Observer::GetCurrentWorldState()
{
    return m_aCurrentWorldState;
}

void Observer::Update(float fDeltaTime)
{
    //if the world state has been updated 
    if(m_bWSUpdated)
    {
        //Update the expected world state
        FindExpectedWorldState();

        //find out if there was a deviation
        FindDeviations();

        //if a deviation was found
        if(!m_apDeviations.empty())
        {
            //Get an explanation for this happening
            auto& rsExplanation = GenerateExplanation();

        	//TODO: Send message to Plans Overseer asking for new goal

        }


        //no need to do this again until the world state has changed
        m_bWSUpdated = false;
    }



}

//-------------------------------------------------------------------------------------------------------------
// Protected Functions 
//-------------------------------------------------------------------------------------------------------------

std::string& Observer::GenerateExplanation()
{
    // TODO: insert return statement here
}

void Observer::FindDeviations()
{
    m_apDeviations.clear();

    //This could be simplified, but then it wouldn't be an iterator -> needs to be iterator so it can return nothing if nothing is found
    //for every expected world state
    for(auto rIt : m_aExpectedWorldState)
    {
        //If this is a deviation -> current world state is different from the expected world state
        if(CheckDeviation(rIt.first))
        {
            m_apDeviations.push_back(rIt);
        }
    }
 
}



bool Observer::CheckDeviation(const std::string& rsWorldState)
{
    //Find both 
    const auto& rCurrIterator = m_aCurrentWorldState.find(rsWorldState);
    const auto& rExpeIterator = m_aExpectedWorldState.find(rsWorldState);

    //if it exists in both
    if(rCurrIterator != m_aCurrentWorldState.end() && rExpeIterator != m_aExpectedWorldState.end())
    {
        //return if they are the same value
        return rCurrIterator->second == rExpeIterator->second;
    }

    return false;
}

void Observer::FindExpectedWorldState()
{
    //Clear the world state
    m_aExpectedWorldState.clear();

    //Get a reference to the current plan
    const ActionList& rapPlan = m_pManager->GetCurrentPlan();

   const int nIndex = m_pManager->GetCurrentAction();



    //if within bounds and the action exists
    if(nIndex < rapPlan.size() && rapPlan[nIndex])
    {
        //reference to the required world state of the current action
    	const WorldStateList& rasCurReqWS = rapPlan[nIndex]->GetReqWS();

        //add every requirement -> needs to be true or we cant do this action
		for(int i = 0; i < rasCurReqWS.size();i++)
		{
            m_aExpectedWorldState.insert_or_assign(rasCurReqWS[i],true);
		}

        //make sure this has nothing on it
        m_arsSatisfiedWS.clear();

        //we need this done first
        //add every actions satisfied ws onto this list
        for(int i = 0; i < rapPlan.size(); i++)
        {
            m_arsSatisfiedWS.push_back(rapPlan[i]->GetSatWS());
        }

        //for every action after the current action
        for(int i = nIndex + 1; i < rapPlan.size(); i++)
        {
            //get reference to the list of required WS
            const WorldStateList& rasWS = rapPlan[i]->GetReqWS();

            //for every requirement of every action after the current action
            for(int j = 0; j < rasWS.size(); j++)
            {
                //find if it exists on the satisfied world state
                auto pIterator = std::find(m_arsSatisfiedWS.begin(),m_arsSatisfiedWS.end(), rasWS[j]);

                //if not on the list
                if(pIterator == m_arsSatisfiedWS.end())
                {
                    //then this is expected to be true -> without we cant complete plan
                    //and not satisfied by a world state
                    m_aExpectedWorldState.insert_or_assign(rasWS[j], true);
                }
            }
        }

    }

}