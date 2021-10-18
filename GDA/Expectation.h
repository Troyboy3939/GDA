#pragma once
#include <string>
#include <functional>

class Manager;

class Expectation
{
public:
	Expectation(std::string& rsExpectation, std::function<bool(Manager* pManager)>& fnCheckDeviation);

	std::string& GetExpectation();

	bool CheckDevation(Manager* pManager);

private:
	std::function<bool(Manager* pManager)> m_fnCheckDeviation;
	std::string m_sExpectation;
};

