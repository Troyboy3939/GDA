#include "Storage.h"

Storage::Storage(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{


	Initialise(pTexture, pLocation, pTeam,v3Cost);
}

Storage::Storage() : Building()
{

	m_eBuildingType = Building::BType::Storage;
}

void Storage::Update(float fDeltaTime)
{
	Building::Update(fDeltaTime);
}

void Storage::Draw(aie::Renderer2D* pRenderer)
{
	Building::Draw(pRenderer);
}

void Storage::Initialise(aie::Texture* pTexture, Tile* pLocation, Empire* pTeam, Vector3 v3Cost)
{
	Building::Initialise(pTexture, pLocation, pTeam,v3Cost);


	m_eBuildingType = Building::BType::Storage;

	
}

float Storage::GetProgress()
{
	return 0.0f;
}
