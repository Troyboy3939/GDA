#include "ActionBase.h"
#include "Manager.h"




ActionBase::~ActionBase()
{
}

float ActionBase::GetCost()
{
    return m_fCost;
}

std::string ActionBase::GetSatWS()
{
    return m_sSatWorldState;
}

std::vector<std::string> ActionBase::GetReqWS()
{
    return m_asReqWorldState;
}

void ActionBase::AddEffect(std::string sWS, bool bValue)
{
    //add the effect
    m_Effects.insert_or_assign(sWS, bValue);
}

std::unordered_map<std::string, bool> ActionBase::GetEffects()
{
    return m_Effects;



}

