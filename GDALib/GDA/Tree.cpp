#include "Tree.h"
#include "Goal.h"
#include "Action.h"
#include "Node.h"

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
	Delete(m_pRootNode);
}



void Tree::AddNode(Node* pNode, Node* pParent)
{
	pParent->AddChild(pNode);


	pNode->SetParent(pParent);

}

void Tree::Clear()
{
	Delete(m_pRootNode);
}

void Tree::SetGoal(Goal* pGoal)
{
	//make sure the tree is empty
	Clear();

	//Set the root node
	//                      Action, Parent, hSCore, Goal
	m_pRootNode = new Node(nullptr, nullptr, 0, pGoal);




}

Node* Tree::GetGoal()
{
	return m_pRootNode;
}

void Tree::Delete(Node* pNode)
{
	if (pNode && m_pRootNode)
	{
		std::vector<Node*>& rChildren = pNode->GetChildren();

		//for every child
		for (int i = 0; i < rChildren.size(); i++)
		{
			Delete(rChildren[i]);
		}

		

		//if there are no children, delete
		delete pNode;

	}
}

