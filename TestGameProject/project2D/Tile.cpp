#include "Tile.h"


Tile::Tile(Vector2 v2Pos, aie::Texture* pTexture)
{
	m_pTexture = pTexture;
	m_v2Position = v2Pos;


	m_fGScore = 0.0f;
	m_fHScore = 0.0f;


	m_bDrawConnection = false;
	m_bDrawGrid = false;
	m_pPrevious = nullptr;

	m_apNeighbours.reserve(8);

	for (int i = 0; i < 8; i++)
	{
		m_apNeighbours.push_back(nullptr);
	}
}

Tile::~Tile()
{
}

void Tile::Update(float fDeltaTime)
{
}

void Tile::Draw(aie::Renderer2D* pRenderer)
{

	if (pRenderer)
	{
		pRenderer->drawSprite(m_pTexture, m_v2Position.x, m_v2Position.y, static_cast<float>( m_pTexture->getWidth()), static_cast<float>(m_pTexture->getHeight()), 0, 100.0f);

		if (m_bDrawConnection)
		{
			pRenderer->setRenderColour(0.0f, 0.0f, 1.0f);
			for (int i = 0; i < m_apNeighbours.size(); i++)
			{
				if (m_apNeighbours[i] && m_bOn && m_apNeighbours[i]->m_bOn)
				{
					pRenderer->drawLine(m_v2Position.x, m_v2Position.y, m_apNeighbours[i]->m_v2Position.x, m_apNeighbours[i]->m_v2Position.y);
				}
			}

		}

		if (m_bDrawGrid)
		{
			pRenderer->setRenderColour(1.0f, 0.0f, 0.0f);

			auto fWidth = static_cast<float>(m_pTexture->getWidth());
			auto fHeight = static_cast<float>(m_pTexture->getHeight());

			Vector2 v2TR = Vector2(m_v2Position.x + fWidth / 2, m_v2Position.y + fHeight / 2);

			Vector2 v2TL = Vector2(m_v2Position.x - fWidth / 2, m_v2Position.y + fHeight / 2);
	

			Vector2 v2BL = Vector2(m_v2Position.x - fWidth / 2, m_v2Position.y - fHeight / 2);


			Vector2 v2BR = Vector2(m_v2Position.x + fWidth / 2, m_v2Position.y - fHeight / 2);
	

			pRenderer->drawLine(v2BL.x, v2BL.y, v2BR.x, v2BR.y,1.5f,1);
			pRenderer->drawLine(v2TL.x, v2TL.y, v2TR.x, v2TR.y, 1.5f,1);
			pRenderer->drawLine(v2TL.x, v2TL.y, v2BL.x, v2BL.y,1.5f,1);
			pRenderer->drawLine(v2TR.x, v2TR.y, v2BR.x, v2BR.y, 1.5f,1);

		}

		//m_bDrawGrid = false;
		pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	}
}

void Tile::AddNeighbour(Tile* pTile, Connection eCon)
{


	m_apNeighbours[static_cast<int>(eCon)] = pTile;

}

float Tile::GetFScore()
{
	return m_fGScore + m_fHScore;
}

float Tile::GetGScore()
{
	return m_fGScore;
}

float Tile::GetHScore()
{
	return m_fHScore;
}

void Tile::SetGScore(float fScore)
{
	m_fGScore = fScore;
}

void Tile::SetHScore(float fScore)
{
	m_fHScore = fScore;
}

Tile* Tile::GetPrevious()
{
	return m_pPrevious;
}

void Tile::SetPrevious(Tile* pTile)
{
	m_pPrevious = pTile;
}

Vector2 Tile::GetPosition()
{
	return m_v2Position;
}

Tile::Neighbours & Tile::GetNeighbours()
{
	return m_apNeighbours;
}

Tile* Tile::GetNeighbour(Connection eTile)
{
	auto nIndex = static_cast<int>(eTile);
	if (nIndex > -1 && nIndex < m_apNeighbours.size())
	{
		return m_apNeighbours[nIndex];
	}

	return nullptr;
}

void Tile::Highlight()
{
	m_bDrawGrid = true;
}

void Tile::SetOn(bool bOn)
{
	m_bOn = bOn;
}

bool Tile::GetOn()
{
	return m_bOn;
}

aie::Texture* Tile::GetTexture()
{
	return m_pTexture;
}

bool Tile::CanPlaceBuilding()
{

	//If this one is on (bottom left)
	if (m_bOn)
	{
		//if bottom right is on
		if (m_apNeighbours[static_cast<int>(Connection::Right)] && m_apNeighbours[static_cast<int>(Connection::Right)]->GetOn())
		{
			// and top is on
			if (m_apNeighbours[static_cast<int>(Connection::Top)] && m_apNeighbours[static_cast<int>(Connection::Top)]->GetOn())
			{

				//and finally top right is on
				if (m_apNeighbours[static_cast<int>(Connection::TopRight)] && m_apNeighbours[static_cast<int>(Connection::TopRight)]->GetOn())
				{
					//then we can place a building here
					return true;
				}
			}
		}
	}


	return false;
}
