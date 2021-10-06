#include "Message.h"

//constructor with initialiser list to assign the reference
Message::Message(std::vector<unsigned int>& anToID, std::string sMessage, void* pData, std::string sType) : m_anToID(anToID)
{
    m_pData = pData;
    m_sDataType = sType;
    m_sMessage = sMessage;
}
std::vector<unsigned int>& Message::GetRecieverID()
{
    return m_anToID;
}

bool Message::CheckID(unsigned int nID)
{
    return std::find(m_anToID.begin(),m_anToID.end(), nID) != m_anToID.end();
}

std::string& Message::GetMessage()
{
    return m_sMessage;
}

void Message::SetMessage(std::string sMessage)
{
    m_sMessage = sMessage;
}

void* Message::GetData()
{
    return m_pData;
}

std::string& Message::GetDataType()
{
    return m_sDataType;
}
