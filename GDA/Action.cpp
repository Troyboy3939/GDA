#include "Action.h"

Action::Action()
{
    m_fCost = 0;

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

