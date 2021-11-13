#include "FloorHeap.h"
#include "Tile.h"


FloorHeap::FloorHeap()
{
}

FloorHeap::~FloorHeap()
{
}

void FloorHeap::Add(Tile* pTile)
{
	//Add Tile to heap
	m_aTiles.push_back(pTile);

	//Get the index of the Tile added
	int nCurrent = (int)(m_aTiles.size() - 1);
	//Get the parent of the Tile added
	int nParent = GetParent(nCurrent);


	//Fix the heap 
	while (m_aTiles[nCurrent]->GetFScore() < m_aTiles[nParent]->GetFScore())
	{
		Tile* pSwap = m_aTiles[nCurrent];
		m_aTiles[nCurrent] = m_aTiles[nParent];
		m_aTiles[nParent] = pSwap;

		nCurrent = nParent;
		nParent = GetParent(nCurrent);
	}
}



Tile* FloorHeap::GetTop()
{
	if (m_aTiles.size() == 0)
	{
		return nullptr;
	}


	//store Top Tile
	Tile* pTile = m_aTiles[0];

	//Get the last Tile index
	int nLast = (int)(m_aTiles.size() - 1);

	//set the new top Tile to the last Tile
	m_aTiles[0] = m_aTiles[nLast];

	m_aTiles.pop_back();

	int nCurrent = 0;
	int nChild1Index = GetChild(0,1);
	int nChild2Index = GetChild(0, 2);
	int nCheapestIndex = nChild1Index;

	if (nCheapestIndex >= m_aTiles.size())
		return pTile;

	if (nChild2Index < m_aTiles.size() && m_aTiles[nChild2Index]->GetFScore() < m_aTiles[nChild1Index]->GetFScore())
	{
		nCheapestIndex = nChild2Index;
	}

	while (m_aTiles[nCheapestIndex]->GetFScore() < m_aTiles[nCurrent]->GetFScore())
	{
		Tile* pSwap = m_aTiles[nCheapestIndex];
		m_aTiles[nCheapestIndex] = m_aTiles[nCurrent];
		m_aTiles[nCurrent] = pSwap;

		nCurrent = nCheapestIndex;
		nChild1Index = GetChild(nCurrent, 1);
		nChild2Index = GetChild(nCurrent, 2);

		nCheapestIndex = nChild1Index;
		if (nCheapestIndex >= m_aTiles.size())
		{
			return pTile;
		}
		if (nChild2Index < m_aTiles.size() && m_aTiles[nChild2Index]->GetFScore() < m_aTiles[nCheapestIndex]->GetFScore())
		{
			nCheapestIndex = nChild2Index;
		}

	}
	return pTile;
}

int FloorHeap::Size()
{
	return (int)m_aTiles.size();
}

void FloorHeap::Clear()
{
	m_aTiles.clear();
}

bool FloorHeap::Find(Tile* pTile)
{

	for (int i = 0; i < m_aTiles.size(); i++)
	{
		if (m_aTiles[i] == pTile)
		{
			return pTile;

		}
	}
	return false;
}

int FloorHeap::GetChild(int nIndex, int nChild)
{
	return (2 * nIndex) + nChild;
}

int FloorHeap::GetParent(int nIndex)
{
	return (nIndex - 1) / 2;
}
