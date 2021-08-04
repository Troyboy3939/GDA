#include "Heap.h"
#include "Node.h"
Heap::Heap()
{
}

Heap::~Heap()
{
}

void Heap::Add(Node* pNode)
{
	//Add node to heap
	m_aNodes.push_back(pNode);

	//Get the index of the node added
	int nCurrent = (int)(m_aNodes.size() - 1);
	//Get the parent of the node added
	int nParent = GetParent(nCurrent);


	//Fix the heap 
	while (m_aNodes[nCurrent]->GetFScore() < m_aNodes[nParent]->GetFScore())
	{
		Node* pSwap = m_aNodes[nCurrent];
		m_aNodes[nCurrent] = m_aNodes[nParent];
		m_aNodes[nParent] = pSwap;

		nCurrent = nParent;
		nParent = GetParent(nCurrent);
	}
}

Node* Heap::GetTop()
{
	if (m_aNodes.size() == 0)
	{
		return nullptr;
	}


	//store Top Node
	Node* pNode = m_aNodes[0];

	//Get the last node index
	int nLast = (int)(m_aNodes.size() - 1);

	//set the new top node to the last node
	m_aNodes[0] = m_aNodes[nLast];

	m_aNodes.pop_back();

	int nCurrent = 0;
	int nChild1Index = GetChild(0,1);
	int nChild2Index = GetChild(0, 2);
	int nCheapestIndex = nChild1Index;

	if (nCheapestIndex >= m_aNodes.size())
		return pNode;

	if (nChild2Index < m_aNodes.size() && m_aNodes[nChild2Index]->GetFScore() < m_aNodes[nChild1Index]->GetFScore())
	{
		nCheapestIndex = nChild2Index;
	}

	while (m_aNodes[nCheapestIndex]->GetFScore() < m_aNodes[nCurrent]->GetFScore())
	{
		Node* pSwap = m_aNodes[nCheapestIndex];
		m_aNodes[nCheapestIndex] = m_aNodes[nCurrent];
		m_aNodes[nCurrent] = pSwap;

		nCurrent = nCheapestIndex;
		nChild1Index = GetChild(nCurrent, 1);
		nChild2Index = GetChild(nCurrent, 2);

		nCheapestIndex = nChild1Index;
		if (nCheapestIndex >= m_aNodes.size())
		{
			return pNode;
		}
		if (nChild2Index < m_aNodes.size() && m_aNodes[nChild2Index]->GetFScore() < m_aNodes[nCheapestIndex]->GetFScore())
		{
			nCheapestIndex = nChild2Index;
		}

	}
	return pNode;
}

int Heap::Size()
{
	return (int)m_aNodes.size();
}

void Heap::Clear()
{
	m_aNodes.clear();
}

bool Heap::Find(Node* pNode)
{

	for (int i = 0; i < m_aNodes.size(); i++)
	{
		if (m_aNodes[i] == pNode)
		{
			return pNode;

		}
	}
	return false;
}

int Heap::GetChild(int nIndex, int nChild)
{
	return (2 * nIndex) + nChild;
}

int Heap::GetParent(int nIndex)
{
	return (nIndex - 1) / 2;
}
