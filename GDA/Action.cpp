#include "Action.h"
#include "Manager.h"




Action::Action(float fCost, std::function<bool(Manager* pManager)>* pIsValidFuction, void* pData, std::string sType)
{
    m_fCost = fCost;
    m_pIsValid = pIsValidFuction;

    m_pData = pData;
    m_sDataType = sType;
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
    m_Effects.insert_or_assign(sWS, bValue);
}

std::unordered_map<std::string, bool> Action::GetEffects()
{
    return m_Effects;



}

bool Action::IsValid(Manager* pManager)
{
    if (m_pIsValid)
    {
        return (*m_pIsValid)(pManager);
    }

    return false;
}

void* Action::GetData()
{
    return m_pData;
}

std::string Action::GetDataType()
{
    return m_sDataType;
}

void Action::SetData(void* pData)
{
    m_pData = pData;
}

void Action::SetDataType(std::string sType)
{
    m_sDataType = sType;
}

