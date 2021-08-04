#pragma once
#include <vector>

class Action;
class Goal;

class Node
{
public:
	void CreateAction(Action* pAction, Node* pParent);
	void CreateGoal(Goal* pGoal);


	float GetFScore();
	float GetGScore();
	float GetHScore();
private:
	Action* m_pAction;
	Goal* m_pGoal;
	bool m_bIsAction;
	Node* m_pParent;
	std::vector<Node*> m_apChildren;

	//Scores for A*
	float m_fFScore;
	float m_fGScore;
	float m_fHScore;
	

};

