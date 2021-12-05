#pragma once
#include <vector>
#include <unordered_map>
class Node;

class NodePool
{
public:
	NodePool();
	~NodePool();

	Node* GetNode();

	void Return(Node* pNode);

private:
	std::unordered_map<Node*, bool> m_InUse;

	std::vector<Node*> m_apNodes;


};

