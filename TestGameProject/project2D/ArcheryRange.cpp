#include "ArcheryRange.h"
#include "Empire.h"
ArcheryRange::ArcheryRange(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Initialise(pTexture, pLocation, pTeam, v3Cost);
}

ArcheryRange::ArcheryRange() : Building()
{
	m_eBuildingType = Building::BType::ArcheryRange;

	m_fTimer = -1.0f;

	m_fUnitTime = 10.0f;
	m_fUpgradeTime = 20.0f;
}

ArcheryRange::~ArcheryRange()
{
}

void ArcheryRange::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Building::Initialise(pTexture, pLocation, pTeam,v3Cost);
	m_eBuildingType = Building::BType::ArcheryRange;
	m_fTimer = -1.0f;
}

void ArcheryRange::Update(float fDeltaTime)
{
	Building::Update(fDeltaTime);
	if (!m_aActionQueue.empty())
	{
		auto pAction = m_aActionQueue[0];

		

		switch (pAction)
		{
		case Icon::IType::ArcAtt:
		case Icon::IType::ArcSpe:
		case Icon::IType::ArcDef:
		{
			if (m_fTimer <= 0.0f)
			{
				m_fTimer = fDeltaTime;
			}
			else
			{
				m_fTimer += fDeltaTime;

				if (m_fTimer >= m_fUpgradeTime)
				{
					m_pTeam->UpgradeUnit(pAction);
					m_fTimer = -1.0f;

					//erase this element off the queue
					m_aActionQueue.erase(m_aActionQueue.begin());
				}
			}



		}
		break;
		case Icon::IType::Archer:
		case Icon::IType::Skirmisher:
		{
			if (m_fTimer <= 0.0f)
			{
				m_fTimer = fDeltaTime;
			}
			else
			{
				m_fTimer += fDeltaTime;

				if (m_fTimer >= m_fUnitTime)
				{
					Unit::UType eUnit;

					if (pAction == Icon::IType::Archer)
					{
						eUnit = Unit::UType::Archer;
					}
					else
					{
						eUnit = Unit::UType::Skirmisher;
					}

					m_pTeam->CreateUnit(m_v2Position, eUnit);
					m_fTimer = -1.0f;

					//erase this element off the queue
					m_aActionQueue.erase(m_aActionQueue.begin());
				}
			}
		}
		break;
		default:
			break;
		}

	}
}

void ArcheryRange::Draw(aie::Renderer2D* pRenderer)
{
	Building::Draw(pRenderer);
}

float ArcheryRange::GetProgress()
{
	if (!m_aActionQueue.empty())
	{
		switch (m_aActionQueue[0])
		{
		case Icon::IType::Archer:
		case Icon::IType::Skirmisher:
			return m_fTimer / m_fUnitTime;
			break;
		case Icon::IType::ArcAtt:
		case Icon::IType::ArcDef:
		case Icon::IType::ArcSpe:
			return m_fTimer / m_fUpgradeTime;
			break;
		}

	}

	return 0.0f;
}
