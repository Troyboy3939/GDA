#include "ResourceManager.h"
#include "ResourceClass.h"
#include "Floor.h"
ResourceManager::ResourceManager(float fTreeAmount, float fGoldAmount, float fBerryAmount, Floor* pFloor)
{

	
	m_apResources.reserve(600);

	m_pFloor = pFloor;

	m_fTreeAmount  = fTreeAmount;
	m_fGoldAmount  = fGoldAmount;
	m_fBerryAmount = fBerryAmount;

	m_pTreeTexture =  new aie::Texture("Textures/Trees/RE_00.png");
	m_pGoldTexture = new aie::Texture("Textures/Gold.png");
	m_pBerryTexture = new aie::Texture("Textures/Berry.png");


	CreateForests();

	CreateBerryBushes();
	
	CreateGoldMines();
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < m_apResources.size(); i++)
	{
		delete m_apResources[i];
	}

}

void ResourceManager::Update(float fDeltaTime)
{

	for (int i = 0; i < m_apResources.size(); i++)
	{
		m_apResources[i]->Update(fDeltaTime);
	}
}

void ResourceManager::Draw(aie::Renderer2D* pRenderer)
{

	for (int i = 0; i < m_apResources.size(); i++)
	{
		m_apResources[i]->Draw(pRenderer);
	}
}

Resource* ResourceManager::GetResourceAtLocation(Vector2 v2Location)
{

	for (int i = 0; i < m_apResources.size(); i++)
	{
		Vector2 v2LocToResource = m_apResources[i]->GetPosition() - v2Location;


		if (v2LocToResource.magnitudeSq() < 30 * 30 && m_apResources[i]->GetResourcesLeft() > 0.0f)
		{
			return m_apResources[i];
		}
	}

	return nullptr;

}


Resource* ResourceManager::GetClosestResource(Vector2 v2Location, Resource::Type eType)
{

	Resource* pResource = nullptr;

	float fDistance = 0.0f;
	for (int i = 0; i < m_apResources.size(); i++)
	{
		if (m_apResources[i]->GetType() == eType || eType == Resource::Type::NoResources)
		{




			Vector2 v2LocToResource = m_apResources[i]->GetPosition() - v2Location;


			if (pResource)
			{


				if (v2LocToResource.magnitudeSq() < fDistance && m_apResources[i]->GetResourcesLeft() > 0.0f)
				{
					pResource = m_apResources[i];
					fDistance = v2LocToResource.magnitudeSq();
				}
			}
			else if (m_apResources[i] && m_apResources[i]->GetResourcesLeft() > 0.0f)
			{
				pResource = m_apResources[i];
				fDistance = v2LocToResource.magnitudeSq();
			}
		}
		
	}

	
	return pResource;
}

Resource* ResourceManager::FindNearbyResource(Vector2 v2Location)
{

	for (int i = 0; i < m_apResources.size();i++)
	{
		Vector2 v2Dis = v2Location - m_apResources[i]->GetPosition();

		if (v2Dis.magnitudeSq() < 200 * 200 && m_apResources[i]->GetResourcesLeft() > 0.0f)
		{
			return m_apResources[i];
		}
	}

	return nullptr;
}

void ResourceManager::CreateForests()
{

	

	//Forest 1
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			Vector2 v2Pos(50.0f + x * m_pTreeTexture->getWidth(),800.0f + y * 128.0f * 1.1f);

			m_apResources.push_back(new Resource(m_fTreeAmount, Resource::Type::WOOD, m_pFloor->PosToTile(v2Pos), m_pTreeTexture));
		
		}
	}

	//Forest 2
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 5; y++)
		{

			Vector2 v2Pos(1600.0f + x * m_pTreeTexture->getHeight(), 2800.0f + y * m_pTreeTexture->getHeight());
			m_apResources.push_back(new Resource(m_fTreeAmount, Resource::Type::WOOD, m_pFloor->PosToTile(v2Pos), m_pTreeTexture));
		}
	}
	
	
	//Forest 3
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			Vector2 v2Pos(800.0f + x * m_pTreeTexture->getHeight(), 4700.0f - y * m_pTreeTexture->getHeight());
	
			m_apResources.push_back(new Resource(m_fTreeAmount, Resource::Type::WOOD, m_pFloor->PosToTile(v2Pos), m_pTreeTexture));
		}
	}
	
	
	//Forest 4
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			Vector2 v2Pos(4200.0f + x * m_pTreeTexture->getHeight(), 50 + y * m_pTreeTexture->getHeight());
	
			m_apResources.push_back(new Resource(m_fTreeAmount, Resource::Type::WOOD, m_pFloor->PosToTile(v2Pos), m_pTreeTexture));
		}
	}



}

void ResourceManager::CreateGoldMines()
{
	//Player Gold mines 
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Vector2 v2Pos(200.0f + x * 75.0f, 375.0f + y * 75.0f);
			m_apResources.push_back(new Resource(m_fGoldAmount, Resource::Type::GOLD, m_pFloor->PosToTile(v2Pos), m_pGoldTexture));
		
		}
	}
	
	//Add tenth gold mine to player
	m_apResources.push_back(new Resource(m_fGoldAmount, Resource::Type::GOLD, m_pFloor->PosToTile( Vector2(420.0f, 375.0f)), m_pGoldTexture));


	//AI Gold mines 
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Vector2 v2Pos(4000.0f + x * 75.0f, 3460.0f + y * 75.0f);
			m_apResources.push_back(new Resource(m_fGoldAmount, Resource::Type::GOLD, m_pFloor->PosToTile(v2Pos), m_pGoldTexture));

		}
	}

	//Add tenth gold mine to AI
	m_apResources.push_back(new Resource(m_fGoldAmount, Resource::Type::GOLD, m_pFloor->PosToTile(Vector2(4000.0f, 3666.0f)), m_pGoldTexture));

	

	//Middle Gold
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			Vector2 v2Pos(2800.0f + x * 75.0f, 2000.0f + y * 75.0f);
			m_apResources.push_back(new Resource(m_fGoldAmount, Resource::Type::GOLD, m_pFloor->PosToTile(v2Pos), m_pGoldTexture));

		}
	}



}

void ResourceManager::CreateBerryBushes()
{
	//Player berry bushes 
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Vector2 v2Pos(1500.0f + x * 40.0f, 200.0f + y * 40.0f);
			m_apResources.push_back(new Resource(m_fBerryAmount, Resource::Type::FOOD, m_pFloor->PosToTile(v2Pos), m_pBerryTexture));

		}
	}

	//3300 4100
	//Add tenth berry bush to player
	m_apResources.push_back(new Resource(m_fBerryAmount, Resource::Type::FOOD, m_pFloor->PosToTile(Vector2(1500.0f, 320.0f)), m_pBerryTexture));


//	//AI berry bush 
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			Vector2 v2Pos(3300.0f + x * 64.0f, 4100.0f + y * 64.0f);
			m_apResources.push_back(new Resource(m_fBerryAmount, Resource::Type::FOOD, m_pFloor->PosToTile(v2Pos), m_pBerryTexture));
	
		}
	}
	
	//Add tenth berry bush to AI
	m_apResources.push_back(new Resource(m_fBerryAmount, Resource::Type::FOOD, m_pFloor->PosToTile(Vector2(3520.0f, 4200.0f)), m_pBerryTexture));



	//Middle berry bush
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			Vector2 v2Pos(1800.0f + x * 40.0f, 1900.0f + y * 40.0f);
			m_apResources.push_back(new Resource(m_fBerryAmount, Resource::Type::FOOD, m_pFloor->PosToTile(v2Pos), m_pBerryTexture));

		}
	}

}
