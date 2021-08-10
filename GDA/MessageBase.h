#pragma once
#include <unordered_map>
#include <vector>
#include <algorithm>
class MessageBase
{
public:
	MessageBase(std::vector<unsigned int> anToID, std::string sMessage);
	std::vector<unsigned int> GetRecieverID();

	bool CheckID(unsigned int nID);



	bool CheckPassThrough(unsigned int nID);

	std::string GetMessage();
protected:
	//who the message is for
	std::vector<unsigned int> m_anToID;

	//who the message has been checked by
	std::unordered_map<int, bool> m_aPassed;

	std::string m_sMessage;
};

