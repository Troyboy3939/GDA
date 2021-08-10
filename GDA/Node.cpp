#include "Node.h"
#include "Action.h"


Node::Node()
{
	m_pAction = nullptr;
	m_pGoal = nullptr;
	m_pParent = nullptr;

	m_fGScore = 0;
	m_fHScore = 0;

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

std::vector<std::string> Node::GetReqWS()
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
