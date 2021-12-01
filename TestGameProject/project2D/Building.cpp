#include "Building.h"
#include "Texture.h"
#include "Floor.h"
#include "Empire.h"
Building::Building(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Initialise(pTexture,pLocation, pTeam, v3Cost);
}

Building::Building()
{
	m_v2Position = Vector2();
	m_pTexture = nullptr;
	m_eBuildingType = BType::NoTypes;
	m_fPercentageComplete = 0.0f;
	m_pTeam = nullptr;
	m_pFloor = nullptr;
	m_fFood = 0.0f;
	m_fWood = 0.0f;
	m_fGold = 0.0f;
	
	m_fHealth = 2000.0f;
}

Building::~Building()
{
}

void Building::Update(float fDeltaTime)
{
	if (m_fHealth < 0.0f)
	{
		m_pTeam->ReturnBuilding(this);
	}


}

void Building::Draw(aie::Renderer2D* pRenderer)
{
	if (pRenderer)
	{
		if (m_fPercentageComplete < 100.0f)
		{
			//this will make any incomplete building get lighter and more towards what it should look like 
			//the more it gets complete. But incomplete buildings will appear darkened to signify that they aren't complete
			pRenderer->setRenderColour(m_fPercentageComplete / 100.0f, m_fPercentageComplete / 100.0f, m_fPercentageComplete / 100.0f);
		}

		pRenderer->drawSprite(m_pTexture, m_v2Position.x, m_v2Position.y, 0.0f, 0.0f, 0.0f, 98.0f);

		pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);

	}

}

void Building::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	if (pTexture && pTeam)
	{
		m_fHealth = 2000.0f;
		m_pTile = pLocation;
		m_pTeam = pTeam;
		GameObject::Initialise(pLocation);
		m_fPercentageComplete = 0.0f;

		auto nWidth = pLocation->GetTexture()->getWidth();
		auto nHeight = pLocation->GetTexture()->getHeight();

		m_v2Position.x += (static_cast<float>(nWidth / 2.0f));
		m_v2Position.y += (static_cast<float>(nHeight / 2.0f));


		m_pBottomLeft = pLocation;

		m_eBuildingType = BType::NoTypes;

		m_pFloor = pTeam->GetFloor();

		m_pTexture = pTexture;

		TurnTilesOff();


		m_pTeam->SetWood(m_pTeam->GetWood() - v3Cost.x);
		m_pTeam->SetFood(m_pTeam->GetFood() - v3Cost.y);
		m_pTeam->SetGold(m_pTeam->GetGold() - v3Cost.z);

	}

}

Building::BType Building::GetBuildingType()
{
	return m_eBuildingType;
}

Icons& Building::GetIcons()
{
	return m_apIcons;
}

float Building::GetPercentageComplete()
{
	return m_fPercentageComplete;
}

void Building::SetPercentageComplete(float fPercentage)
{
	m_fPercentageComplete = fPercentage;
}

Tile* Building::GetTile()
{
	return m_pBottomLeft;
}

Icon* Building::GetCurrentAction()
{
	if (!m_aActionQueue.empty())
	{
		return m_aActionQueue[0];
	}


	return nullptr;
}

void Building::AddActionToQueue(Icon* pIcon)
{
	m_aActionQueue.push_back(pIcon);
}

int Building::GetActionsLeft()
{
	return m_aActionQueue.size();
}

float Building::GetGold()
{
	return m_fGold;
}

float Building::GetWood()
{
	return m_fWood;
}

float Building::GetFood()
{
	return m_fFood;
}

void Building::SetFood(float fFood)
{
	m_fFood = fFood;
}

void Building::SetWood(float fWood)
{
	m_fWood = fWood;
}

void Building::SetGold(float fGold)
{
	m_fGold = fGold;
}

Empire* Building::GetTeam()
{
	return m_pTeam;
}

float Building::GetHealth()
{
	return m_fHealth;
}

void Building::SetHealth(float fHealth)
{
	m_fHealth = fHealth;
}

void Building::TurnTilesOff()
{
	
	if (m_pBottomLeft)
	{
		auto& rapNeigh = m_pBottomLeft->GetNeighours();


		if (rapNeigh[static_cast<int>(Tile::Connection::TopRight)])
		{
			rapNeigh[static_cast<int>(Tile::Connection::TopRight)]->SetOn(false);
		}

		if (rapNeigh[static_cast<int>(Tile::Connection::Top)])
		{
			rapNeigh[static_cast<int>(Tile::Connection::Top)]->SetOn(false);
		}

		if (rapNeigh[static_cast<int>(Tile::Connection::Right)])
		{
			rapNeigh[static_cast<int>(Tile::Connection::Right)]->SetOn(false);
		}



	}



}
