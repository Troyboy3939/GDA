#pragma once
#include <vector>

class Node;

class Heap
{
public:

	

	Heap();
	~Heap();


	Node* GetTop();
	int Size();
	void Clear();
	void Add(Node* pNode);
	bool Find(Node* pNode);
private:


	int GetChild(int nIndex, int nChild);
	int GetParent(int nIndex);
	std::vector<Node*> m_aNodes;
};

