#pragma once
#include <map>
#include <string>

class Observer
{
public:

	
	std::map<std::string, bool>& GetCurrentWorldState();

private:
	std::map<std::string, bool> m_CurrentWorldState;
};

