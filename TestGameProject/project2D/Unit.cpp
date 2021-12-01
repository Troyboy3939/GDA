#include "Unit.h"
#include "Empire.h"
#include "UnitPool.h"
Unit::Unit(Tile* pLocation, Empire* pTeam)
{
	Initialise(pLocation,pTeam);
}

Unit::Unit() : GameObject()
{
	m_pTeam = nullptr;
	m_fHealth = 100.0f;
	m_fRadius = 10.0f;
	m_bInUse = false;
	m_nSpeUpgrade = 0;
	
}


Unit::~Unit()
{
}

void Unit::Update(float fDeltaTime)
{
	


	if (m_fHealth <= 0.0f)
	{
 		m_pTeam->ReturnUnit(this);
		return;
	}


	//calculate the path steering behaviour


	
	Vector2 v2ToPath;
	Vector2 v2PathForce;
	Vector2 v2SeperationForce;
	Vector2 v2AlignmentForce;
	Vector2 v2CohesionForce;



	//---------------------------------------------------
	// Calculate seek force towards next point in path
	//---------------------------------------------------

	//if there is a path that can be followed
  	if (m_av2Path.size() > 0 && m_nPath > -1 && m_nPath < m_av2Path.size())
	{

		v2ToPath = m_av2Path[m_nPath] - m_v2Position;


		if (v2ToPath.magnitudeSq() < m_fSkipDistance * m_fSkipDistance)
		{
			m_nPath++;

			if (m_nPath >= m_av2Path.size())
			{
				m_nPath--;

				//reset destination

				auto v2Dis = m_v2Destination - m_v2Position;

				if (v2Dis.magnitudeSq() < 12 * 12)
				{
					m_v2Destination = Vector2(0.0f, 0.0f);
				}

				m_av2Path.clear();


				for (auto pUnit : m_apGroup)
				{
					if (pUnit)
					{
						pUnit->m_apGroup.clear();
					}
				}

				m_apGroup.clear();
			}

		}

		if (!m_av2Path.empty())
		{
			v2PathForce = Arrive(m_av2Path[m_nPath]);
		}

	}
	else //theres no path (maybe on top of a bush,tree or TC or something where theres no nodes)
	{
		m_nPath = 0;

		m_av2Path.clear();

		if (!m_v2Destination.isZero())
		{

			v2ToPath =  m_v2Destination - m_v2Position;


			
			v2PathForce = Arrive(m_v2Destination);

		}

	}




	//---------------------------------------------------
	// Calculate Seperation force
	//---------------------------------------------------
	Separate(v2SeperationForce);


	//if you do not have a destination then don't do anything
	if (!m_v2Destination.isZero())
	{

		//---------------------------------------------------
		// Calculate the alignment force and centre of mass (cohesion)
		//---------------------------------------------------
		Vector2 v2CenterOfMass;
		AlignmentCohesion(v2AlignmentForce, v2CenterOfMass);


		//---------------------------------------------------
		//	final calculations for alignment and cohesion forces
		//---------------------------------------------------
		if (m_apGroup.size() > 0)
		{
			v2AlignmentForce /= m_apGroup.size();

			if (m_v2Velocity.magnitudeSq() > 0.0f)
			{
				v2AlignmentForce -= m_v2Velocity.Normalised();
			}

			//average this to get a centre of mass
			v2CenterOfMass /= m_apGroup.size();

			//vector from position towards the center of mass
			auto v2ToCentOfMass = v2CenterOfMass - m_v2Position;

			auto v2Dest = v2ToCentOfMass.GetReflection() + m_v2Destination;

			//if (v2Dest.magnitudeSq() <  12 * 12)
			//{
			//	//m_v2Destination = Vector2(0.0f,0.0f);
			//	//m_av2Path.clear();
			//	
			//	for (auto pUnit : m_apGroup)
			//	{
			//		if (pUnit)
			//		{
			//			pUnit->m_apGroup.clear();
			//		}
			//	}
			//
			//	m_apGroup.clear();
			//
			//	//skip this frame 
			//	return;
			//}



			//seek towards center of mass -> this force when added will bring them to the centre
			v2CohesionForce = Arrive(v2CenterOfMass);
		}
	}


	if (m_v2Destination.isZero())
	{
		m_v2Velocity = Vector2(0.0f,0.0f);
	}

	//weight the steering forces
	m_v2Steering = (v2PathForce * 1.0f)+ (v2SeperationForce * 1.0f) + (v2AlignmentForce * 0.5f) + (v2CohesionForce * 0.05f);

	m_v2Velocity += m_v2Steering;

	if (m_v2Velocity.magnitudeSq() > 0.0f)
	{
		m_v2Velocity.normalise();
		m_v2Velocity *= m_fMaxSpeed + (20.0f * m_nSpeUpgrade);
		m_v2Position += m_v2Velocity * fDeltaTime;
	}


	

}

void Unit::Draw(aie::Renderer2D* pRenderer)
{
	if (pRenderer)
	{
		auto& v3Colour = m_pTeam->GetTeamColour();

		pRenderer->setRenderColour(v3Colour.x, v3Colour.y, v3Colour.z);

		//Draw villager
		pRenderer->drawCircle(m_v2Position.x, m_v2Position.y, m_fRadius, 98.0f);
		pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);

		//for (int i = 0; i + 1< m_av2Path.size(); i++)
		//{
		//	pRenderer->drawLine(m_av2Path[i].x,m_av2Path[i].y, m_av2Path[i + 1].x, m_av2Path[i + 1].y);
		//}
	}

}

void Unit::Initialise(Tile* pLocation, Empire* pTeam)
{
	
	GameObject::Initialise(pLocation);
	pLocation->SetOn(true);
	m_pTeam = pTeam;

	m_fRadius = 10.0f;
	m_nPath = 0;

	m_fSkipDistance = 50;

	m_fMaxSpeed = 100.0f;
	m_nSpeUpgrade = 0;
	m_bInUse = true;
}

Unit::UType Unit::GetUnitType()
{
	return m_eUnitType;
}

float Unit::GetHealth()
{
	return m_fHealth;
}

void Unit::SetHealth(float fHealth)
{
	m_fHealth = fHealth;
}

float Unit::GetRadius()
{
	return m_fRadius;
}

void Unit::MoveTo(Vector2 v2Location)
{
	auto pFloor = m_pTeam->GetFloor();

	pFloor->GetPath(m_v2Position,v2Location, m_av2Path);

	m_v2Destination = v2Location;
	m_nPath = 0;

}

std::vector<Unit*>& Unit::GetGroup()
{
	return m_apGroup;
}

int Unit::GetSpeUpgrade()
{
	return m_nSpeUpgrade;
}

Empire* Unit::GetTeam()
{
	return m_pTeam;
}

Vector2 Unit::Seek(Vector2 v2Location)
{
	Vector2 v2ToLoc = v2Location - m_v2Position;


	return (v2ToLoc.Normalised()  * m_fMaxSpeed) - m_v2Velocity;
}

Vector2 Unit::Arrive(Vector2 v2Location)
{
	Vector2 v2ToLoc = v2Location - m_v2Position;

	auto fMag = v2ToLoc.magnitude();

	if (fMag > 0.0f)
	{


		auto fSpeed = (fMag / 0.3f);

		if (fSpeed > m_fMaxSpeed)
		{
			fSpeed = m_fMaxSpeed;
		}


		Vector2 v2Desired = v2ToLoc * fSpeed / fMag;


		return v2Desired - m_v2Velocity;

	}


	return Vector2();
}

void Unit::Separate(Vector2& rv2Force)
{

	//Get the object pool so that you can steer away from all units, not just the group that you are in
	auto pUnitPool = m_pTeam->GetUnitPool();

	auto& rapUnits = pUnitPool->GetPool();

	for (auto pUnit : rapUnits)
	{
		if (pUnit == this)
		{
			continue;
		}


		//if it exists and is in use
		if (pUnit && pUnit->m_bInUse)
		{
			Vector2 v2ToUnit = m_v2Position - pUnit->GetPosition();


			auto fMag = v2ToUnit.magnitude();

			if (fMag < 40.0f)
			{

				auto fAmountOfOverlap = pUnit->m_fRadius + pUnit->m_fRadius - fMag;

				if (fAmountOfOverlap >= 0.0f)
				{
					m_v2Position += (v2ToUnit / fMag) * fAmountOfOverlap;
					//return;
				}


				if (!v2ToUnit.isZero())
				{
					//rv2Force += v2ToUnit.Normalised() / v2ToUnit.magnitude();
				}
			}
		}
	}


}

void Unit::AlignmentCohesion(Vector2& rv2AForce, Vector2& rv2CentreOfMass)
{
	
	//calculate alignment and cohesion forces
	for (int i = 0; i < m_apGroup.size(); i++)
	{
		auto pUnit = m_apGroup[i];

		if (pUnit && pUnit->m_bInUse)
		{
			if (pUnit == this)
			{
				//erase yourself from te group
				m_apGroup.erase(m_apGroup.begin() + i);
				continue;
			}
			//Alignment force calculation
			if (!pUnit->m_v2Velocity.isZero())
			{

				rv2AForce += pUnit->m_v2Velocity.Normalised();
			}

			rv2CentreOfMass += pUnit->GetPosition();
		}
	}

}


/*

	

*/