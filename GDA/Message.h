#pragma once
#include <vector>
#include "MessageBase.h"




template<typename Data>
class Message : public MessageBase
{
public:
	template<typename Data>
	Message(Data pData, std::vector<unsigned int> anToID, std::string sMessage) : MessageBase( anToID, sMessage)
	{
		m_pData = pData;
	}

	Data GetData()
	{
		return m_pData;
	}
protected:
	Data m_pData;
};

