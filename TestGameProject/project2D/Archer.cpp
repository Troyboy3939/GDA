#include "Archer.h"
#include "BuildingPool.h"
#include "UnitPool.h"
#include "Empire.h"

Archer::Archer() : MilitaryUnit()
{
	m_eUnitType = Unit::UType::Archer;
	m_fArrowSpeed = 800;
	m_fAttackLerp = -1.0f;
	m_fAttackTimer = 3.0f;

	m_fAttackCooldown = 1.0f;
}

Archer::Archer(Tile* pLocation, Empire* pTeam)
{
	Initialise(pLocation, pTeam);
	m_eUnitType = Unit::UType::Archer;
}

Archer::~Archer()
{
}

void Archer::Initialise(Tile* pTile, Empire* pTeam)
{
	MilitaryUnit::Initialise(pTile, pTeam);
	m_eUnitType = Unit::UType::Archer;
}

void Archer::Update(float fDeltaTime)
{
	MilitaryUnit::Update(fDeltaTime);

	if (m_fAttackLerp >= 0.0f)
	{
		// v = d / t -> vt = d
		auto fDistanceTravelled = m_fArrowSpeed * fDeltaTime;

		//  distance travelled this frame / total distance to travel 
		// use this to create a percentage an use that to lerp
		m_fAttackLerp += fDistanceTravelled / m_fDisToTarg;
	}
}

void Archer::Draw(aie::Renderer2D* pRenderer)
{
	MilitaryUnit::Draw(pRenderer);

	pRenderer->setRenderColour(128.0f / 255.0f, 0.0f, 0.0f);

	//draw circle on top of the initial circle to show that this is an archer
	pRenderer->drawCircle(m_v2Position.x, m_v2Position.y, m_fRadius * 0.6f, 97.0f);

	if (m_fAttackLerp >= 0.0f && m_fAttackLerp <=  1.0f && m_pAttacking)
	{

		pRenderer->setRenderColour(89.0f / 255.0f, 48.0f / 255.0f, 24.0f / 255.0f);

		//interpolate between the current position and the position of the this you are attacking
		auto v2ArrowPos = Vector2(Vector2::Lerp(m_v2Position.x, m_pAttacking->GetPosition().x, m_fAttackLerp), Vector2::Lerp(m_v2Position.y, m_pAttacking->GetPosition().y, m_fAttackLerp));

		pRenderer->drawCircle(v2ArrowPos.x, v2ArrowPos.y, 3.0f, 97.0f);

	}
	pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
}

void Archer::Upgrade(Icon::IType eUpgrade)
{
	if (eUpgrade == Icon::IType::ArcAtt)
	{
		m_nAttUpgrade++;
	}
	else if (eUpgrade == Icon::IType::ArcDef)
	{
		m_nDefUpgrade++;
	}
	else
	{
		m_nSpeUpgrade++;
	}
}

void Archer::AttackBuilding(float fDeltaTime)
{

	if (m_pAttacking)
	{

		auto pBuilding = static_cast<Building*>(m_pAttacking);

		//Vector from unit towards this unit
		Vector2 v2ToBuilding = pBuilding->GetPosition() - m_v2Position;

		m_fDisToTarg = v2ToBuilding.magnitude();

		//if within 10 squares of the unit
		if (m_fDisToTarg < 640)
		{

			m_v2Velocity = Vector2();
			m_v2Destination = Vector2();
			m_av2Path.clear();

			if (m_fAttackTimer >= m_fAttackCooldown)
			{
				m_fAttackTimer = 0.0f;
				//start lerp
				if (m_fAttackLerp < 0.0f)
				{
					m_fAttackLerp = 0.0f;
				}

				//take roughly 3 hits to kill enemy
				auto fAttackAmount = 100 / 3.0f;


				auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();

				if (nUpgrade > 0)
				{
					fAttackAmount *= nUpgrade * 1.25f;
				}

				if (m_fAttackLerp >= 1.0f)
				{
					pBuilding->SetHealth(pBuilding->GetHealth() - fAttackAmount);
					m_fAttackLerp = -1.0f;
					m_fAttackTimer = 0.0f;
				}

				if (pBuilding->GetHealth() <= 0.0f)
				{
					auto pPool = m_pTeam->GetBuildPool();


					m_pAttacking = pPool->GetClosestBuilding(pBuilding, 1000.0f, m_pTeam);

				}

			}
			else
			{
				m_fAttackTimer += fDeltaTime;
			}
		}
		else if (m_pAttacking)
		{
			MoveTo(m_pAttacking->GetPosition());
		}

	}


}

void Archer::AttackUnit(float fDeltaTime)
{

	if (m_pAttacking)
	{

		auto pUnit = static_cast<Unit*>(m_pAttacking);

		//Vector from unit towards this unit
		Vector2 v2ToUnit = pUnit->GetPosition() - m_v2Position;

		 m_fDisToTarg = v2ToUnit.magnitude();

		//if within 10 squares of the unit
		if (m_fDisToTarg < 640)
		{

			m_v2Velocity = Vector2();
			m_v2Destination = Vector2();
			m_av2Path.clear();

			if (m_fAttackTimer >= m_fAttackCooldown)
			{
				m_fAttackTimer = 0.0f;
				//start lerp
				if (m_fAttackLerp < 0.0f)
				{
					m_fAttackLerp = 0.0f;
				}
				
				
				



				//take roughly 4 hits to kill enemy
				auto fAttackAmount = 25.0f;

				//figure out 
				switch (pUnit->GetUnitType())
				{
					//Standard damage
				case Unit::UType::Villager:
				case Unit::UType::Archer:
				case Unit::UType::Scout:
				case Unit::UType::Knight:
				case Unit::UType::Skirmisher:
				{
					auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();

					if (nUpgrade > 0)
					{
						fAttackAmount *= nUpgrade * 1.25f;
					}

					if (m_fAttackLerp >= 1.0f)
					{
						pUnit->SetHealth(pUnit->GetHealth() - fAttackAmount);
						m_fAttackLerp = -1.0f;
						m_fAttackTimer = 0.0f;
					}
				}
				break; //double damage
				case Unit::UType::Swordsman:
				case Unit::UType::Pikeman:
				{
					auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();

					fAttackAmount *= 2 + (nUpgrade * 1.25f);

					if (m_fAttackLerp >= 1.0f)
					{
						pUnit->SetHealth(pUnit->GetHealth() - fAttackAmount);
						m_fAttackLerp = -1.0f;
						m_fAttackTimer = 0.0f;
					}
				}
				break;
				}

				if (pUnit->GetHealth() <= 0.0f)
				{
					auto pPool = m_pTeam->GetUnitPool();


					m_pAttacking = pPool->GetClosestUnit(pUnit, 1000.0f, m_pTeam);

				}

			}
			else
			{
				m_fAttackTimer += fDeltaTime;
			}
		}
		else if (m_pAttacking)
		{
			MoveTo(m_pAttacking->GetPosition());
		}

	}


}
