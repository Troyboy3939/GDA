#pragma once
#include <vector>

class Action;
class Goal;

class Node
{
public:

	Node();

	void SetParent(Node* pNode);



	float GetFScore();
	float GetGScore();
	float GetHScore();

	std::vector<Node*>& GetChildren();
	std::vector<std::string> GetReqWS();

	void SetReqWS(std::vector<std::string> asReqWS);

	void AddReqWS(std::string sWS);
	

	void SetGScore(float fGscore);
	void SetHScore(float fHscore);

	void AddChild(Node* pNode);
private:
	Action* m_pAction;
	Goal* m_pGoal;
	Node* m_pParent;
	std::vector<Node*> m_apChildren;
	std::vector<std::string> m_asReqWS;

	//Scores for A*
	float m_fGScore;
	float m_fHScore;
	

};

