#include "Tile.h"


Tile::Tile(Vector2 v2Pos, aie::Texture* pTexture)
{
	m_pTexture = pTexture;
	m_v2Position = v2Pos;
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
		pRenderer->drawSprite(m_pTexture,m_v2Position.x,m_v2Position.y,m_pTexture->getWidth(),m_pTexture->getHeight(),0,100.0f);
	}
}
