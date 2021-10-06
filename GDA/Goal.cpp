#include "Goal.h"




Goal::Goal(std::string& rsReqWS, std::function<bool(Manager* pManager)>* pIsValidFunction, std::string& rsType, void* pData)
{

	m_sReqWorldState = rsReqWS;

	m_pIsValid = pIsValidFunction;

	m_pData = pData;
	m_sDataType = rsType;
}

Goal::~Goal()
{
}


std::string& Goal::GetRequiredWorldState()
{
	return m_sReqWorldState;
}

bool Goal::IsValid(Manager* pManager)
{
	return (*m_pIsValid)(pManager);
}

void* Goal::GetData()
{
	return m_pData;
}

std::string& Goal::GetDataType()
{
	return m_sDataType;
}

void Goal::SetData(void* pData)
{
	m_pData = pData;
}

void Goal::SetDataType(std::string& sType)
{
	m_sDataType = sType;
}

