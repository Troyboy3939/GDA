#pragma once
#include <string>
#include <functional>
#include "PlansOverseer.h"
class Manager;

class Expectation
{
public:
	Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation);
	Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation, std::function<PlansOverseer::RiskSeverity(Manager* pManager)>& fnRiskAnalysis);


	std::string& GetExpectation();

	bool CheckDevation(Manager* pManager);


	PlansOverseer::RiskSeverity RiskAnalysis(Manager* pManager);

private:
	std::function<bool(Manager* pManager)> m_fnCheckDeviation;
	std::function<PlansOverseer::RiskSeverity(Manager* pManager)> m_fnRiskAnalysis;

	std::string m_sExpectation;
};

