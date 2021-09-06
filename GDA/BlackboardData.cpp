#include "BlackboardData.h"

BlackboardData::BlackboardData(void* pData, std::string sDataType)
{
    m_pData = pData;
    m_sDataType = sDataType;
}

std::string BlackboardData::GetDataType()
{
    return m_sDataType;
}

void* BlackboardData::GetData()
{
    return m_pData;
}
