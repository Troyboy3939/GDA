#include "AIComponent.h"
#include "Blackboard.h"
#include "PlansOverseer.h"
#include "EcoManager.h"
#include "MilitaryManager.h"

AIComponent::AIComponent(Empire* pTeam) : InputComponent(pTeam)
{

	m_pPlansOverseer = new PlansOverseer();
	m_pBlackboard = new Blackboard(m_pPlansOverseer);
	m_pPlansOverseer->SetBlackboard(m_pBlackboard);

	m_pEcoManager = new EcoManager(m_pBlackboard,this);
	m_pMilitaryManager = new MilitaryManager(m_pBlackboard);
	
	m_pBlackboard->AddManager(m_pEcoManager);
	m_pBlackboard->AddManager(m_pMilitaryManager);
}

AIComponent::~AIComponent()
{
	if (m_pPlansOverseer)
	{
		delete m_pPlansOverseer;
		m_pPlansOverseer = nullptr;
	}

	if (m_pBlackboard)
	{
		delete m_pBlackboard;
		m_pBlackboard = nullptr;
	}

	if (m_pEcoManager)
	{
		delete m_pEcoManager;
		m_pEcoManager = nullptr;
	}

	if (m_pMilitaryManager)
	{
		delete m_pMilitaryManager;
		m_pMilitaryManager = nullptr;
	}

}

void AIComponent::Update(float fDeltaTime)
{
	if (m_pEcoManager)
	{
		m_pEcoManager->Update(fDeltaTime);
	}

	if (m_pMilitaryManager)
	{
		m_pMilitaryManager->Update(fDeltaTime);
	}


	
}

void AIComponent::Draw(aie::Renderer2D* pRenderer)
{
}
