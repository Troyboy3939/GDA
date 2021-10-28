#pragma once
#include <unordered_map>
#include <vector>
#include <algorithm>

using Recipients = std::vector<unsigned int>;

class Message
{
public:
	//-----------------------------------
	// Constructor for creating a new message
	//-----------------------------------
	Message(Recipients& anToID, std::string&& sMessage, void* pData = nullptr, std::string&& sType = "");


	//-----------------------------------
	// Get the list of ID who this message is intended for
	//-----------------------------------
	std::vector<unsigned int>& GetRecieverID();


	//-----------------------------------
	// Check if this message is intended for nID
	//-----------------------------------
	bool CheckID(unsigned int nID);



	
	//-----------------------------------
	// Get the message string
	//-----------------------------------
	std::string& GetMessage();


	//-----------------------------------
	// Change the message string
	//-----------------------------------
	void SetMessage(const std::string& sMessage);

	//---------------------
	// Get the data associated 
	// with the message
	//---------------------	
	void* GetData();

	//---------------------
	// Return a string that 
	// has the name of the 
	// 	data type of m_pData
	//---------------------	
	std::string& GetDataType();
protected:
	//who the message is for
	Recipients m_anToID;

	//who the message has been checked by
	std::unordered_map<int, bool> m_aPassed;

	std::string m_sMessage;

	//Data and the data type 
	std::string m_sDataType;
	void* m_pData;
};

