#include "ResourceClass.h"

Resource::Resource(float fAmountOfResources, Type eType, Vector2 v2Position, aie::Texture* pTexture) : GameObject(v2Position)
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

	if (pRenderer)
	{
		pRenderer->drawSprite(m_pTexture, m_v2Position.x, m_v2Position.y,128,128,0.0f,1.0f);
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
}

float Resource::GetResourcesLeft()
{
	return m_fResourcesLeft;
}
