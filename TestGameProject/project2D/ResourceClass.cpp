#include "ResourceClass.h"
#include "Tile.h"
Resource::Resource(float fAmountOfResources, Type eType, Tile* pTile, aie::Texture* pTexture) : GameObject(pTile)
{
	m_fResourcesLeft = fAmountOfResources;
	m_pTexture = pTexture;
	m_eType = eType;

}

void Resource::Update(float fDeltaTime)
{
}

void Resource::Draw(aie::Renderer2D* pRenderer)
{

	if (pRenderer && m_fResourcesLeft > 0.0f)
	{
		pRenderer->drawSprite(m_pTexture, m_v2Position.x, m_v2Position.y,128,128,0.0f,98.0f);
	}
	

}

Resource::Type Resource::GetType()
{
	return m_eType;
}

void Resource::SetType(Type eType)
{
	m_eType = eType;
}

void Resource::Collect(float fAmount)
{

	m_fResourcesLeft -= fAmount;

	if (m_fResourcesLeft <= 0.0f)
	{
		m_pTile->SetOn(true);
	}
}

float Resource::GetResourcesLeft()
{
	return m_fResourcesLeft;
}

Vector2 Resource::GetPosition()
{
	return m_v2Position;
}
