#include "Goal.h"




Goal::Goal(std::string sReqWS, std::function<bool(Manager* pManager)>* pIsValidFunction, void* pData, std::string sType)
{

	m_sReqWorldState = sReqWS;

	m_pIsValid = pIsValidFunction;

	m_pData = pData;
	m_sDataType = sType;
}

Goal::~Goal()
{
}


std::string Goal::GetRequiredWorldState()
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

std::string Goal::GetDataType()
{
	return m_sDataType;
}

void Goal::SetData(void* pData)
{
	m_pData = pData;
}

void Goal::SetDataType(std::string sType)
{
	m_sDataType = sType;
}

