#include "Tree.h"
#include "Goal.h"
#include "Action.h"
#include "Node.h"
#include "NodePool.h"
Tree::Tree(Goal* pGoal)
{

	//Set the goal
	SetGoal(pGoal);
}

Tree::Tree()
{
	m_pRootNode = nullptr;
}

Tree::~Tree()
{
}



void Tree::AddNode(Node* pNode, Node* pParent)
{
	pParent->AddChild(pNode);


	pNode->SetParent(pParent);

}

void Tree::Clear(NodePool* pNodePool)
{
	Delete(m_pRootNode, pNodePool);
}

void Tree::SetGoal(Goal* pGoal)
{

	//Set the root node
	//                      Action, Parent, hSCore, Goal
	m_pRootNode = new Node(nullptr, nullptr, 0, pGoal);




}

Node* Tree::GetGoal()
{
	return m_pRootNode;
}

void Tree::Delete(Node* pNode, NodePool* pNodePool)
{
	if (pNode && m_pRootNode)
	{
		std::vector<Node*>& rChildren = pNode->GetChildren();

		//for every child
		for (int i = 0; i < rChildren.size(); i++)
		{
			Delete(rChildren[i],pNodePool);
		}

		rChildren.clear();

		//if there are no children, delete
		if (pNodePool)
		{
			pNode->SetParent(nullptr);


			pNodePool->Return(pNode);

		}

	}
}

