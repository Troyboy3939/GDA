#include "NodePool.h"
#include "Node.h"

NodePool::NodePool()
{
	m_apNodes.reserve(25);

	for (int i = 0; i < 25; i++)
	{
		m_apNodes.push_back(new Node());
	}
}

NodePool::~NodePool()
{
	for (auto pNode : m_apNodes)
	{
		if (pNode)
		{
			delete pNode;
		}
	}
}

Node* NodePool::GetNode()
{

	for (auto pNode : m_apNodes)
	{
		if (!m_InUse[pNode])
		{
			m_InUse[pNode] = true;
			return pNode;
		}
	}


	auto pNode = new Node();
	m_InUse[pNode] = true;

	m_apNodes.push_back(pNode);
	return pNode;
}

void NodePool::Return(Node* pNode)
{
	m_InUse[pNode] = false;
}
