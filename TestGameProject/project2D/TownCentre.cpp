#include "TownCentre.h"

TownCentre::TownCentre(aie::Texture* pTexture,Vector2 v2Location) : Building(pTexture,v2Location)
{
}

TownCentre::TownCentre()
{
}

TownCentre::~TownCentre()
{
}

void TownCentre::Update(float fDeltaTime)
{
}

void TownCentre::Draw(aie::Renderer2D* pRenderer)
{
	pRenderer->drawSprite(m_pTexture,m_v2Position.x,m_v2Position.y);
}
