#pragma once
#include <string>
class BlackboardData
{
public:
	BlackboardData(void* pData, std::string sDataType);

	std::string GetDataType();
	
	void* GetData();

private:

	std::string m_sDataType;
	void* m_pData;
};

