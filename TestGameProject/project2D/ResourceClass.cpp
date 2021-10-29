#include "ResourceClass.h"

Resource::Resource(float fAmountOfResources, Type eType, Vector2 v2Position) : GameObject(v2Position)
{
	m_fResourcesLeft = fAmountOfResources;

	m_eType = eType;
}

void Resource::Update(float fDeltaTime)
{
}

void Resource::Draw(aie::Renderer2D* pRenderer)
{
	switch (m_eType)
	{
	case Type::FOOD:
		pRenderer->setRenderColour(75 / 255,65 / 255,186 / 255);
		pRenderer->drawBox(m_v2Position.x,m_v2Position.y,50,50);
		pRenderer->setRenderColour(1,1,1);
		break;
	case Type::GOLD:
		pRenderer->setRenderColour(199 / 255, 190 / 255, 30 / 255);
		pRenderer->drawCircle(m_v2Position.x, m_v2Position.y, 50);
		pRenderer->setRenderColour(1, 1, 1);
		break;
	case Type::WOOD:
		pRenderer->setRenderColour(33 / 255, 94 / 255, 50 / 255);
		pRenderer->drawCircle(m_v2Position.x, m_v2Position.y, 50);
		pRenderer->setRenderColour(1, 1, 1);
		break;
	default:
		return;
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
