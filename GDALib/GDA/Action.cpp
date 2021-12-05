	#include "Action.h"
#include "Manager.h"




Action::Action(float fCost, std::function<bool(Manager* pManager)>& rfnIsValidFuction, const std::string& rsSatWS, std::initializer_list<std::string> asReq, const std::string& rsType, void* pData)
{
    m_fCost = fCost;
    m_pIsValid = std::move(rfnIsValidFuction);

    m_pData = pData;
    m_sDataType = rsType;
}

Action::Action(float fCost, std::function<bool(Manager* pManager)>& rfnIsValidFuction, const std::string& rsSatWS, std::initializer_list<std::string> asReq)
{
    m_fCost = fCost;
    m_pIsValid = std::move(rfnIsValidFuction);

    m_pData = nullptr;
    m_sDataType = "void*";

    m_sSatWorldState = std::move(rsSatWS);

    m_asReqWorldState.insert(m_asReqWorldState.begin(), asReq);
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
        return m_pIsValid(pManager);
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

void Action::SetID(int nID)
{
    m_nID = nID;
}

int Action::GetID()
{
    return m_nID;
}

