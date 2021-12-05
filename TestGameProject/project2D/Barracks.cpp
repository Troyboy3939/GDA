#include "Barracks.h"
#include "Empire.h"
Barracks::Barracks(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Initialise(pTexture, pLocation, pTeam, v3Cost);

	m_fTimer = -1.0f;

	m_fUnitTime = 10.0f;
	m_fUpgradeTime = 20.0f;
}

Barracks::Barracks() : Building()
{
		m_eBuildingType = Building::BType::Barracks;
		m_fTimer = -1.0f;

		m_fUnitTime = 10.0f;
		m_fUpgradeTime = 20.0f;
}

Barracks::~Barracks()
{
}

void Barracks::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
		Building::Initialise(pTexture,pLocation,pTeam,v3Cost);
		m_eBuildingType = Building::BType::Barracks;


}

void Barracks::Update(float fDeltaTime)
{
	Building::Update(fDeltaTime);
	if (!m_aActionQueue.empty())
	{
		auto pAction = m_aActionQueue[0];



		switch (pAction)
		{
		case Icon::IType::InfAtt:
		case Icon::IType::InfSpe:
		case Icon::IType::InfDef:
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
		case Icon::IType::Swordsman:
		case Icon::IType::Pikeman:
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

					if (pAction == Icon::IType::Swordsman)
					{
						eUnit = Unit::UType::Swordsman;
					}
					else
					{
						eUnit = Unit::UType::Pikeman;
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

void Barracks::Draw(aie::Renderer2D* pRenderer)
{
	Building::Draw(pRenderer);
}

float Barracks::GetProgress()
{
	if (!m_aActionQueue.empty())
	{
		switch (m_aActionQueue[0])
		{
		case Icon::IType::Swordsman:
		case Icon::IType::Pikeman:
			return m_fTimer / m_fUnitTime;
			break;
		case Icon::IType::InfAtt:
		case Icon::IType::InfSpe:
		case Icon::IType::InfDef:
			return m_fTimer / m_fUpgradeTime;
			break;
		}

	}

	return 0.0f;
}
