#include "Stable.h"
#include "Empire.h"
Stable::Stable(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Initialise(pTexture, pLocation, pTeam, v3Cost);
}

Stable::Stable() : Building()
{
	m_eBuildingType = Building::BType::Stable;

	m_fTimer = -1.0f;

	m_fUnitTime = 10.0f;
	m_fUpgradeTime = 20.0f;
}

Stable::~Stable()
{
}

void Stable::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Building::Initialise(pTexture, pLocation, pTeam,v3Cost);
	m_eBuildingType = Building::BType::Stable;

	m_fTimer = -1.0f;

	m_fUnitTime = 10.0f;
	m_fUpgradeTime = 20.0f;
}

void Stable::Update(float fDeltaTime)
{
	Building::Update(fDeltaTime);
	if (!m_aActionQueue.empty())
	{
		auto pAction = m_aActionQueue[0];



		switch (pAction->GetIconType())
		{
		case Icon::IType::CavAtt:
		case Icon::IType::CavSpe:
		case Icon::IType::CavDef:
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
					m_pTeam->UpgradeUnit(pAction->GetIconType());
					m_fTimer = -1.0f;

					//erase this element off the queue
					m_aActionQueue.erase(m_aActionQueue.begin());
				}
			}



		}
		break;
		case Icon::IType::Scout:
		case Icon::IType::Knight:
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

					if (pAction->GetIconType() == Icon::IType::Scout)
					{
						eUnit = Unit::UType::Scout;
					}
					else
					{
						eUnit = Unit::UType::Knight;
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

void Stable::Draw(aie::Renderer2D* pRenderer)
{
	Building::Draw(pRenderer);
}

float Stable::GetProgress()
{
	if (!m_aActionQueue.empty())
	{
		switch (m_aActionQueue[0]->GetIconType())
		{
		case Icon::IType::Scout:
		case Icon::IType::Knight:
			return m_fTimer / m_fUnitTime;
			break;
		case Icon::IType::CavAtt:
		case Icon::IType::CavDef:
		case Icon::IType::CavSpe:
			return m_fTimer / m_fUpgradeTime;
			break;
		}

	}

	return 0.0f;
}
