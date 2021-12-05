#include "TownCentre.h"
#include "Empire.h"
TownCentre::TownCentre(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	if (pTeam)
	{
		auto pFloor = pTeam->GetFloor();

		Initialise(pTexture, pLocation, pTeam,v3Cost);

		m_pTeam = pTeam;
	}
}

TownCentre::TownCentre() : Building()
{

	m_fAgeUpTime = 30.0f;
	m_fUpgradeTime = 20.0f;
	m_fVillagerTime = 10.0f;
}

TownCentre::~TownCentre()
{
}

void TownCentre::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{

	if (pTeam)
	{
		auto pFloor = pTeam->GetFloor();


		Building::Initialise(pTexture, pLocation, pTeam,v3Cost);
		m_eBuildingType = Building::BType::TownCentre;

		m_fAgeUpTime = 30.0f;
		m_fUpgradeTime = 20.0f;
		m_fVillagerTime = 10.0f;

		m_fTimer = -1.0f;
	}
}

void TownCentre::Update(float fDeltaTime)
{
	Building::Update(fDeltaTime);

	if (!m_aActionQueue.empty())
	{
			if (m_fTimer > 0.0f)
			{
				m_fTimer += fDeltaTime;
			}
			else
			{
				m_fTimer = fDeltaTime;
			}


			auto eType = m_aActionQueue[0];

			switch (eType)
			{
				case Icon::IType::Villager:
				{
					if (m_fTimer > m_fVillagerTime)
					{
						m_fTimer = -1.0f;

						
						m_pTeam->AddVillager(m_v2Position);

						m_aActionQueue.erase(m_aActionQueue.begin());

					}
				}
					break;
				case Icon::IType::VillInv:
				case Icon::IType::VillSpee:
				{
					if (m_fTimer > m_fUpgradeTime)
					{

						//reset timer and then upgrade unit
						m_fTimer = -1.0f;
						m_pTeam->UpgradeUnit(eType);
						m_aActionQueue.erase(m_aActionQueue.begin());
					
					}
				}
					break;
				case Icon::IType::AgeUp:
				{
					if (m_fTimer > m_fAgeUpTime)
					{
						m_aActionQueue.erase(m_aActionQueue.begin());

						m_pTeam->SetAge(m_pTeam->GetAge() + 1);
					}
				}
				break;
			}
	}
}


void TownCentre::Draw(aie::Renderer2D* pRenderer)
{
	Building::Draw(pRenderer);

}

float TownCentre::GetProgress()
{
	if (!m_aActionQueue.empty())
	{
		switch (m_aActionQueue[0])
		{
		case Icon::IType::Villager:
			return m_fTimer / m_fVillagerTime;
			break;
		case Icon::IType::VillInv:
		case Icon::IType::VillSpee:
			return m_fTimer / m_fUpgradeTime;
			break;
		case Icon::IType::AgeUp:
			return m_fTimer / m_fAgeUpTime;
		}

	}
	
	return 0.0f;
}
