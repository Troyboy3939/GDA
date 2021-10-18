#include "Observer.h"
#include "Manager.h"
#include "Action.h"
#include "Goal.h"
#include "Expectation.h"
//-------------------------------------------------------------------------------------------------------------
// Public Functions
//-------------------------------------------------------------------------------------------------------------

Observer::Observer(Manager* pManager)
{
    m_pManager = pManager;

    m_anRecipients.push_back(0);


    m_pExplanationMessage = new Message(m_anRecipients,"DeviationsFound", m_pManager, "Manager*");

}

Observer::~Observer()
{

    if(m_pExplanationMessage)
    {
        delete m_pExplanationMessage;

        m_pExplanationMessage = nullptr;
    }
}


void Observer::Update(float fDeltaTime)
{
    //Check to see if there are deviations from
    //it expected

	FindDeviations();

    //if there are deviations
    if(!m_apDeviations.empty())
    {
        //Generate Explanations
        GenerateExplanation();


        //Send Message to Plans Overseer -> Get a response 
        m_pManager->MessageBlackboard(m_pExplanationMessage);
        
    }

}

Manager* Observer::GetManager()
{
    return m_pManager;
}

RefStringList& Observer::GetExplanations()
{
    return m_arsExplanations;
}

void Observer::AddExplanation(Expectation* pExpect, std::string& rsExplanation)
{
    m_ExplanationMap.emplace(pExpect, rsExplanation);
}

//-------------------------------------------------------------------------------------------------------------
// Protected Functions 
//-------------------------------------------------------------------------------------------------------------

void Observer::GenerateExplanation()
{
    //clear the list that stores the explanations
    //to the deviations that have occured
    m_arsExplanations.clear();

    //for every deviation
    for(auto pDeviation : m_apDeviations)
    {

        //find out if it is in the map
        auto range = m_ExplanationMap.equal_range(pDeviation);

        //go through every possible explanation and add it to the list of explanations
        for(auto pIt = range.first; pIt != range.second; pIt++)
        {
            m_arsExplanations.emplace_back(pIt->second);
        }
		
    }
}

void Observer::FindDeviations()
{
    m_apDeviations.clear();

    Expectations& rapExpectations = m_pManager->GetExpectations();

    //for every expectation in expectations -> check if its different
    for(auto pExpectation : rapExpectations)
    {
        //if it exists, then check whether it is a deviation
	    if(pExpectation && pExpectation->CheckDevation(m_pManager))
	    {
            //if it is, then add it to the list of deviations
            m_apDeviations.push_back(pExpectation);
	    }
    }

}






