#include "MessageBase.h"

MessageBase::MessageBase(std::vector<unsigned int> anToID, std::string sMessage)
{

    //store who this message is going to
    m_anToID = anToID;

    m_sMessage = sMessage;
}
std::vector<unsigned int> MessageBase::GetRecieverID()
{
    return m_anToID;
}

bool MessageBase::CheckID(unsigned int nID)
{
    return std::find(m_anToID.begin(),m_anToID.end(), nID) != m_anToID.end();
}


bool MessageBase::CheckPassThrough(unsigned int nID)
{
    if (m_aPassed.find(nID) != m_aPassed.end())
    {
        m_aPassed.insert_or_assign(nID, true);
        return true;
    }

    return false;
}

std::string MessageBase::GetMessage()
{
    return std::string();
}
