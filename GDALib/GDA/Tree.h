#pragma once
#include <vector>


class Action;
class Goal;
class Node;

class Tree
{
public:
	

	
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

