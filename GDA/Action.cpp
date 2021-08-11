#include "Action.h"



Action::Action(float fCost,std::function<bool(Manager* pManager)>* pIsValidFuction)
{
    //initialise the cost of the action
    m_fCost = fCost;

    //initialise the function to be called when calling IsValid()
    m_pIsValid = pIsValidFuction;
}

Action::Action(float fCost)
{
    m_fCost = fCost;
}

Action::~Action()
{
}

float Action::GetCost()
{
    return m_fCost;
}

std::string Action::GetSatWS()
{
    return m_sSatWorldState;
}

std::vector<std::string> Action::GetReqWS()
{
    return m_asReqWorldState;
}

void Action::AddEffect(std::string sWS, bool bValue)
{
    //add the effect
    m_Effects.insert_or_assign(sWS,bValue);
}

std::unordered_map<std::string, bool> Action::GetEffects()
{
    return m_Effects;


    
}

bool Action::IsValid(Manager* pManager)
{
    return (*m_pIsValid)(pManager);
}

void Action::SetIsValidFunction(std::function<bool(Manager* pManager)>* pIsValidFunction)
{
    m_pIsValid = pIsValidFunction;
}

