#include "Node.h"
#include "Action.h"
void Node::CreateAction(Action* pAction, Node* pParent)
{
	m_pGoal = nullptr;

	m_pAction = pAction;

	m_bIsAction = true;


	m_pParent = pParent;

	m_fFScore = 0.0f;
	m_fGScore = pAction->GetCost();
	m_fHScore = 0.0f;
}

void Node::CreateGoal(Goal* pGoal)
{
	m_pGoal = pGoal;

	m_pAction = nullptr;

	m_bIsAction = false;
	

	m_pParent = nullptr;

	m_fFScore = 0.0f;
	m_fGScore = 0.0f;
	m_fHScore = 0.0f;


}

float Node::GetFScore()
{
	return m_fFScore;
}

float Node::GetGScore()
{
	return m_fGScore;
}

float Node::GetHScore()
{
	return m_fHScore;
}
