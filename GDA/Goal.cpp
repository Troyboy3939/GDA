#include "Goal.h"




Goal::Goal(std::string& rsReqWS, std::function<bool(Manager* pMan)>& IsValidFunction, ExpecInitList expec, const std::string& rsType, void* pData)
{

	m_sReqWorldState = rsReqWS;

	m_asExpectations.insert(m_asExpectations.begin(),expec);

	m_fnIsValid = std::move(IsValidFunction);

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
	return m_fnIsValid(pManager);
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

Expectations& Goal::GetExpectations()
{
	return m_asExpectations;
}

