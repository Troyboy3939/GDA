#include "Observer.h"
#include "Manager.h"
#include "Action.h"

Observer::Observer(Manager* pManager)
{
    m_pManager = pManager;
    m_aExpectedWorldState = pManager->GetExpectedWS();


}

WorldStateMap& Observer::GetCurrentWorldState()
{
    return m_aCurrentWorldState;
}

void Observer::Update(float fDeltaTime)
{
    DeviationChecker();

}

const Deviation Observer::DeviationChecker()
{
    //This could be simplified, but then it wouldn't be an iterator
    //for every expected world state
    for(auto rIt = m_aExpectedWorldState.begin(); rIt != m_aExpectedWorldState.end(); rIt++ )
    {
        //If this is a deviation
        if(CheckDeviation(rIt->first))
        {
            return rIt;
        }
    }
    return m_aExpectedWorldState.end();
}

bool Observer::CheckDeviation(const std::string& rsWorldState)
{
    //Find both 
    const auto& rCurrIterator = m_aCurrentWorldState.find(rsWorldState);
    const auto& rExpeIterator = m_aExpectedWorldState.find(rsWorldState);

    //if it exists in both
    if(rCurrIterator != m_aCurrentWorldState.end() && rExpeIterator != m_aExpectedWorldState.end())
    {
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

    //----------------------------
    // Firstly, add the requirements
    // because they need to be true
    // in order to do this
    //----------------------------

    //if within bounds and the action exists
    if(nIndex < rapPlan.size() && rapPlan[nIndex])
    {
    	const WorldStateList& rasReqWorldState = rapPlan[nIndex]->GetReqWS();

		for(int i = 0; i < rasReqWorldState.size();i++)
		{
            m_aExpectedWorldState.insert_or_assign(rasReqWorldState[i],true);
		}

        //----------------------------
    	// Next, work all the way up
    	// to the last action to find
    	// any requirements that aren't
    	// satisfied by actions (world
    	// state was already true)
    	//----------------------------

        //for every action after the current action
        for(int i = nIndex + 1; i < rapPlan.size(); i++)
        {
           
                //reference to the list of world states
                const WorldStateList& rasReq = rapPlan[i]->GetReqWS();

                   //for every requirement of every action
                   for (int j = 0; j < rasReq.size(); j++)
                   {
                       auto bSkip = false;
						
                       //Keep repeatitively going backwards
                   	   //until you find an action that satisfies
                   	   //the requirement. This should never
                   	   //be too long, as a new plan will
                       // probably get made anyway before nIndex reaches
                   	   //anything high
                       for(int k = nIndex - 1; k >= 0; k--)
                       {
                           //if the previous action satisfied this actions
                       	   //requirement -> skip
                           if (rasReq[j] == rapPlan[i - k]->GetSatWS())
                           {
                               bSkip = true;
                               break;
                           }

							if(bSkip)
							{
                                break;
							}
                       }


                       m_aExpectedWorldState.insert_or_assign(rasReq[j], true);
                   }
            
	        
        }
    }

}