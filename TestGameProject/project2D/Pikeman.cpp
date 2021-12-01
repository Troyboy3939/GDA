#include "Pikeman.h"
#include "Empire.h"
#include "UnitPool.h"
#include "BuildingPool.h"


Pikeman::Pikeman() : MilitaryUnit()
{
	m_eUnitType = Unit::UType::Pikeman;

	m_fAttackTimer = 3.0f;

	m_fAttackCooldown = 2.0f;


}

Pikeman::Pikeman(Tile* pLocation, Empire* pTeam)
{
	Initialise(pLocation, pTeam);
	m_eUnitType = Unit::UType::Pikeman;
}

Pikeman::~Pikeman()
{
}

void Pikeman::Initialise(Tile* pTile, Empire* pTeam)
{
	MilitaryUnit::Initialise(pTile,pTeam);
}

void Pikeman::Update(float fDeltaTime)
{
	MilitaryUnit::Update(fDeltaTime);
}

void Pikeman::Draw(aie::Renderer2D* pRenderer)
{
	MilitaryUnit::Draw(pRenderer);

	pRenderer->setRenderColour(3.0f / 255.0f, 252.0f / 255.0f, 48.0f / 255.0f);


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



	pRenderer->drawLine(m_v2Position.x + v2TopLeft.x, m_v2Position.y + v2TopLeft.y, m_v2Position.x + v2BottomRight.x, m_v2Position.y + v2BottomRight.y, 1.0f, 96.0f);
	pRenderer->drawLine(m_v2Position.x + v2TopRight.x, m_v2Position.y + v2TopRight.y, m_v2Position.x + v2BottomLeft.x, m_v2Position.y + v2BottomLeft.y, 1.0f, 97.0f);

	pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);

}

void Pikeman::Upgrade(Icon::IType eUpgrade)
{
	if (eUpgrade == Icon::IType::InfAtt)
	{
		m_nAttUpgrade++;
	}
	else if (eUpgrade == Icon::IType::InfDef)
	{
		m_nDefUpgrade++;
	}
	else
	{
		m_nSpeUpgrade++;
	}
}

void Pikeman::AttackBuilding(float fDeltaTime)
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

void Pikeman::AttackUnit(float fDeltaTime)
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


				//take roughly 4 hits to kill enemy
				float fAttackAmount = 25.0f;

				//figure out 
				switch (pUnit->GetUnitType())
				{
						//Standard damage
					case Unit::UType::Villager:
					case Unit::UType::Archer:
					case Unit::UType::Skirmisher:
					case Unit::UType::Pikeman:
					case Unit::UType::Swordsman:
					{
						auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();

						if (nUpgrade > 0)
						{
							fAttackAmount *= nUpgrade * 1.25f;
						}


						pUnit->SetHealth(pUnit->GetHealth() - fAttackAmount);
					}
					break; //double damage
					case Unit::UType::Scout:
					case Unit::UType::Knight:
					{
						auto nUpgrade = m_nAttUpgrade - static_cast<MilitaryUnit*>(m_pAttacking)->GetDefUpgrade();

						fAttackAmount *= 2 + (nUpgrade * 1.25f);

						pUnit->SetHealth(pUnit->GetHealth() - fAttackAmount);
					}
					break;
				}


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
