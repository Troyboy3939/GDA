#include "Tile.h"


Tile::Tile(Vector2 v2Pos, aie::Texture* pTexture)
{
	m_pTexture = pTexture;
	m_v2Position = v2Pos;

	m_bDrawConnection = false;
	m_bDrawGrid = false;
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
		pRenderer->drawSprite(m_pTexture, m_v2Position.x, m_v2Position.y, m_pTexture->getWidth(), m_pTexture->getHeight(), 0, 100.0f);

		if (m_bDrawConnection)
		{
			pRenderer->setRenderColour(0.0f, 0.0f, 1.0f);
			for (int i = 0; i < m_apNeighbours.size(); i++)
			{
				pRenderer->drawLine(m_v2Position.x, m_v2Position.y, m_apNeighbours[i]->m_v2Position.x, m_apNeighbours[i]->m_v2Position.y);
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

		pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	}
}

void Tile::AddNeighbour(Tile* pTile)
{
	m_apNeighbours.push_back(pTile);
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
