#include "Action.h"
#include "Manager.h"




Action::Action(float fCost, std::function<bool(Manager* pManager)>* pIsValidFuction, std::string& rsType, void* pData)
{
    m_fCost = fCost;
    m_pIsValid = pIsValidFuction;

    m_pData = pData;
    m_sDataType = rsType;
}

float Action::GetCost()
{
    return m_fCost;
}

std::string& Action::GetSatWS()
{
    return m_sSatWorldState;
}

WorldStateList& Action::GetReqWS()
{
    return m_asReqWorldState;
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

std::string& Action::GetDataType()
{
    return m_sDataType;
}

void Action::SetData(void* pData)
{
    m_pData = pData;
}

void Action::SetDataType(std::string& rsType)
{
    m_sDataType = rsType;
}

