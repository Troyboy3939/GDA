#include "Expectation.h"
#include "PlansOverseer.h"


Expectation::Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation)
{
	m_sExpectation = std::move(rsExpectation);

	m_fnCheckDeviation = std::move(fnCheckDeviation);


}

Expectation::Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation, std::function<PlansOverseer::RiskSeverity(Manager* pManager)>& fnRiskAnalysis)
{
	m_sExpectation = std::move(rsExpectation);

	m_fnCheckDeviation = std::move(fnCheckDeviation);

	m_fnRiskAnalysis = std::move(fnRiskAnalysis);

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

PlansOverseer::RiskSeverity Expectation::RiskAnalysis(Manager* pManager)
{

	if(m_fnRiskAnalysis != nullptr)
	{
		return m_fnRiskAnalysis(pManager);
	}


	return PlansOverseer::RiskSeverity::NONE;
}
