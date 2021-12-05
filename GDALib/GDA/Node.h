#pragma once
#include <vector>
#include <string>
class Action;
class Goal;

class Node
{
public:


	Node(Action* pAction, Node* pParent, float fHScore ,Goal* pGoal = nullptr);

	Node();

	void Initialise(Action* pAction, Node* pParent, float fHScore, Goal* pGoal = nullptr);



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


	Action* GetAction();
	Goal* GetGoal();


	Node* GetParent();
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

