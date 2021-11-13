#include "Building.h"

Building::Building(aie::Texture* pTexture, Vector2 v2Location)
{
	Initialise(pTexture,v2Location);
	

	m_eBuildingType = BType::NoTypes;

}

Building::Building()
{
	m_v2Position = Vector2();
	m_pTexture = nullptr;
	m_eBuildingType = BType::NoTypes;
}

Building::~Building()
{
}

void Building::Initialise(aie::Texture* pTexture, Vector2 v2Location)
{
	GameObject::Initialise(v2Location);


	m_pTexture = pTexture;

}

Building::BType Building::GetBuildingType()
{
	return m_eBuildingType;
}
