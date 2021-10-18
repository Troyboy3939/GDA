#include "Expectation.h"

Expectation::Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation)
{
	m_sExpectation = std::move(rsExpectation);

	m_fnCheckDeviation = std::move(fnCheckDeviation);

}

std::string& Expectation::GetExpectation()
{
	return m_sExpectation;
}

bool Expectation::CheckDevation(Manager* pManager)
{
	if(m_fnCheckDeviation)
	{
		return m_fnCheckDeviation(pManager);
	}

	return false;
}
