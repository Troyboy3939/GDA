#pragma once
#include <vector>


class Action;
class Goal;
class Node;

class Tree
{
public:
	
	struct Node1
	{
		//pointer to the goal/action
		Action* m_pAction;
		Goal* m_pGoal;

		//parent node
		Node1* m_pParent;
		
		float m_fGscore;
		float m_fHscore;

	};
	
	//----------------------------------------
	//Constructor/Destructors
	//----------------------------------------
	Tree(Goal* pGoal);
	Tree();

	~Tree();



	//----------------------------------------
	//Adds an action onto the tree structure, returns the node created
	//----------------------------------------
	Node* AddAction(Action* pAction, Node* pParent);

	void AddNode(Node* pNode, Node* pParent);
	//----------------------------------------
	//Clears the entire tree
	//----------------------------------------
	void Clear();


	//----------------------------------------
	// Resets the goal of the tree
	//----------------------------------------
	void SetGoal(Goal* pGoal);


	//----------------------------------------
	// Returns the rootnode
	//----------------------------------------
	Node* GetGoal();
private:
	Node* m_pRootNode;

	void Delete(Node* pNode);

};

