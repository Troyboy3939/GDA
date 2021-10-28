#include "Node.h"
#include "Action.h"



Node::Node(Action* pAction, Node* pParent, float fHScore, Goal* pGoal)
{
	m_pAction = pAction;
	m_pGoal = pGoal;
	m_pParent = pParent;

	m_asReqWS = pAction->GetReqWS();


	if (m_pAction)
	{
		m_fGScore = m_pAction->GetCost();

		m_fHScore = fHScore;
	}
	else
	{
		m_fGScore = 0;
		m_fHScore = 0;
	}
}

void Node::SetParent(Node* pNode)
{
	m_pParent = pNode;
}


float Node::GetFScore()
{
	return m_fGScore + m_fHScore;
}

float Node::GetGScore()
{
	return m_fGScore;
}

float Node::GetHScore()
{
	return m_fHScore;
}

std::vector<Node*>& Node::GetChildren()
{
	return m_apChildren;
}

std::vector<std::string>& Node::GetReqWS()
{
	return m_asReqWS;
}


void Node::SetReqWS(std::vector<std::string> asReqWS)
{
	m_asReqWS = asReqWS;
}

void Node::AddReqWS(std::string sWS)
{
	m_asReqWS.push_back(sWS);
}

void Node::AddReqWS(std::vector<std::string>& asWS)
{
	m_asReqWS.insert(m_asReqWS.end(), asWS.begin(),asWS.end());

}

void Node::SetGScore(float fGscore)
{
	m_fGScore = fGscore;
}

void Node::SetHScore(float fHscore)
{
	m_fHScore = fHscore;
}

void Node::AddChild(Node* pNode)
{
	m_apChildren.push_back(pNode);
}

Action* Node::GetAction()
{
	return m_pAction;
}

Goal* Node::GetGoal()
{
	return m_pGoal;
}

Node* Node::GetParent()
{
	return m_pParent;
}
