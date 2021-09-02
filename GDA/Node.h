#pragma once
#include <vector>

class ActionBase;
class GoalBase;

class Node
{
public:


	Node(ActionBase* pAction, Node* pParent, float fHScore ,GoalBase* pGoal = nullptr);

	void SetParent(Node* pNode);



	float GetFScore();
	float GetGScore();
	float GetHScore();

	std::vector<Node*>& GetChildren();
	std::vector<std::string>& GetReqWS();

	void SetReqWS(std::vector<std::string> asReqWS);

	void AddReqWS(std::string sWS);
	void AddReqWS(std::vector<std::string>& asWS);

	void SetGScore(float fGscore);
	void SetHScore(float fHscore);

	void AddChild(Node* pNode);


	ActionBase* GetAction();
	GoalBase* GetGoal();


	Node* GetParent();
private:
	ActionBase* m_pAction;
	GoalBase* m_pGoal;
	Node* m_pParent;
	std::vector<Node*> m_apChildren;
	std::vector<std::string> m_asReqWS;

	//Scores for A*
	float m_fGScore;
	float m_fHScore;
	

};

