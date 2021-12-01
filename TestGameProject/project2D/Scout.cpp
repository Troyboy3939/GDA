#include "Scout.h"
#include "UnitPool.h"
#include "BuildingPool.h"
#include "Empire.h"
Scout::Scout() : MilitaryUnit()
{
	m_eUnitType = Unit::UType::Scout;
}

Scout::Scout(Tile* pLocation, Empire* pTeam)
{
	Initialise(pLocation, pTeam);
	m_eUnitType = Unit::UType::Scout;
}

Scout::~Scout()
{
}

void Scout::Initialise(Tile* pLocation, Empire* pTeam)
{
	MilitaryUnit::Initialise(pLocation, pTeam);
	m_eUnitType = Unit::UType::Scout;
	m_fAttackTimer = 3.0f;

	m_fAttackCooldown = 2.0f;

	m_fMaxSpeed = 200.0f;

}

void Scout::Update(float fDeltaTime)
{
	MilitaryUnit::Update(fDeltaTime);
}

void Scout::Draw(aie::Renderer2D* pRenderer)
{
	MilitaryUnit::Draw(pRenderer);

	pRenderer->setRenderColour(128.0f / 255.0f, 0.0f, 0.0f);

	Vector2 v2TopLeft = Vector2(m_v2Position.x - m_fRadius, m_v2Position.y + m_fRadius) - m_v2Position;
	v2TopLeft.normalise();
	v2TopLeft *= m_fRadius;

	Vector2 v2TopRight = Vector2(m_v2Position.x + m_fRadius, m_v2Position.y + m_fRadius) - m_v2Position;
	v2TopRight.normalise();
	v2TopRight *= m_fRadius;
	Vector2 v2BottomLeft = Vector2(m_v2Position.x - m_fRadius, m_v2Position.y - m_fRadius) - m_v2Position;
	v2BottomLeft.normalise();
	v2BottomLeft *= m_fRadius;
	Vector2 v2BottomRight = Vector2(m_v2Position.x + m_fRadius, m_v2Position.y - m_fRadius) - m_v2Position;
	v2BottomRight.normalise();
	v2BottomRight *= m_fRadius;



	pRenderer->drawLine(m_v2Position.x + v2TopRight.x, m_v2Position.y + v2TopRight.y, m_v2Position.x + v2BottomRight.x, m_v2Position.y + v2BottomRight.y, 1.0f, 96.0f);
	pRenderer->drawLine(m_v2Position.x + v2BottomLeft.x, m_v2Position.y + v2BottomLeft.y, m_v2Position.x + v2BottomRight.x, m_v2Position.y + v2BottomRight.y, 1.0f, 96.0f);
	pRenderer->drawLine(m_v2Position.x + v2TopRight.x, m_v2Position.y + v2TopRight.y, m_v2Position.x + v2BottomLeft.x, m_v2Position.y + v2BottomLeft.y, 1.0f, 97.0f);


	pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);

}

void Scout::Upgrade(Icon::IType eUpgrade)
{
	if (eUpgrade == Icon::IType::CavAtt)
	{
		m_nAttUpgrade++;
	}
	else if (eUpgrade == Icon::IType::CavDef)
	{
		m_nDefUpgrade++;
	}
	else
	{
		m_nSpeUpgrade++;
	}
}

void Scout::AttackBuilding(float fDeltaTime)
{

	//if attacking pointer exists
	if (m_pAttacking)
	{
		//convert it to a building
		auto pBuilding = static_cast<Building*>(m_pAttacking);


		//get a vector from this unit position to the building -> use to get the distance between the two
		Vector2 v2ToBuilding = pBuilding->GetPosition() - m_v2Position;

		//if the distance to the builing is less than 85 pixels (use magnitude squared and 85^2 so save from having to do an expensive square root)
		if (v2ToBuilding.magnitudeSq() < 85 * 85)
		{
			m_v2Velocity = Vector2();
			m_v2Destination = Vector2();
			m_av2Path.clear();
			//if the timer has gone over the cooldown
			if (m_fAttackTimer >= m_fAttackCooldown)
			{
				//reset the timer
				m_fAttackTimer = 0.0f;

				//attack

				//take roughly 3 hits to kill enemy
				float fAttackAmount = 100.0f / 3.0f;

		

				if (m_nAttUpgrade > 0)
				{
					fAttackAmount *= m_nAttUpgrade * 1.25f;
				}



				pBuilding->SetHealth(pBuilding->GetHealth() - fAttackAmount);


				if (pBuilding->GetHealth() <= 0.0f)
				{
					auto pPool = m_pTeam->GetBuildPool();

					if (pPool)
					{
						m_pAttacking = pPool->GetClosestBuilding(pBuilding, 1000.0f, m_pTeam);


					}
				}
			}
			else
			{
				//else add to the timer
				m_fAttackTimer += fDeltaTime;
			}
		}
		else
		{
			//if you are too far away go towards it
			MoveTo(pBuilding->GetPosition());
		}
		
	}
	else
	{
		m_eState = State::Idle;
	}

}

void Scout::AttackUnit(float fDeltaTime)
{
	if (m_pAttacking)
	{
		auto pUnit = static_cast<Unit*>(m_pAttacking);

		//Vector from unit towards this unit
		Vector2 v2ToUnit = pUnit->GetPosition() - m_v2Position;


		//if within 15 pixel of the unit
		if (v2ToUnit.magnitudeSq() < 30 * 30)
		{
			if (m_fAttackTimer >= m_fAttackCooldown)
			{
				m_fAttackTimer = 0.0f;


				//take roughly 3 hits to kill enemy
				float fAttackAmount = 100.0f / 3.0f;

				auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();


				if (nUpgrade > 0)
				{
					fAttackAmount *= nUpgrade * 1.25f;
				}


				if (pUnit->GetUnitType() == Unit::UType::Pikeman)
				{
					fAttackAmount /= 2.0f;
				}


				pUnit->SetHealth(pUnit->GetHealth() - fAttackAmount);


				if (pUnit->GetHealth() <= 0.0f)
				{
					auto pPool = m_pTeam->GetUnitPool();

					if (pPool)
					{
						m_pAttacking = pPool->GetClosestUnit(pUnit, 1000.0f, m_pTeam);
					}
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
