#pragma once
#include <string>
class Goal
{
public:
	Goal();
	~Goal();


	std::string GetRequiredWorldState();

private:
	std::string m_sReqWorldState;
	
};

