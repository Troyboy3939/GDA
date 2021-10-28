#pragma once
//--------------------------------------------------------
//  classes strictly used for messaging. Meant to be used like structs
//--------------------------------------------------------

template<typename Data1, typename Data2>
class Pair
{
public:
	Pair(Data1 d1, Data2 d2)
	{
		m_Data1 = d1;
		m_Data2 = d2;
	}
	Data1 m_Data1;
	Data2 m_Data2;
};


template<typename Data1, typename Data2, typename Data3>
class Triple
{
public:
	Triple(Data1 d1, Data2 d2, Data3 d3)
	{
		m_Data1 = d1;
		m_Data2 = d2;
		m_Data3 = d3;
	}

	Data1 m_Data1;
	Data2 m_Data2;
	Data3 m_Data3;

};

template<typename Data1, typename Data2, typename Data3, typename Data4>
class Quad
{
public:
	template<typename Data1, typename Data2, typename Data3, typename Data4>
	Quad(Data1 d1, Data2 d2, Data3 d3, Data4 d4)
	{
		m_Data1 = d1;
		m_Data2 = d2;
		m_Data3 = d3;
		m_Data4 = d4;
	}

	Data1 m_Data1;
	Data2 m_Data2;
	Data3 m_Data3;
	Data4 m_Data4;

};
