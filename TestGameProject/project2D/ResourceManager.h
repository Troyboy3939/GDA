#pragma once
#include <vector>
#include "Vector2.h"
#include "Renderer2D.h"
#include "ResourceClass.h"
class Floor;

class ResourceManager
{
public:
	//---------------------------------------------
	// 
	//---------------------------------------------
	ResourceManager(float fTreeAmount, float fGoldAmount, float fBerryAmount, Floor* pFloor);
	~ResourceManager();

	//---------------------------------------------
	// 
	//---------------------------------------------
	void Update(float fDeltaTime);

	//---------------------------------------------
	// 
	//---------------------------------------------
	void Draw(aie::Renderer2D* pRenderer);

	//---------------------------------------------
	// 
	//---------------------------------------------
	Resource* GetResourceAtLocation(Vector2 v2Location);


	//---------------------------------------------
	// 
	//---------------------------------------------
	Resource* GetClosestResource(Vector2 v2Location, Resource::Type eType);


	//---------------------------------------------
	// 	   Returns an available resource nearby
	//---------------------------------------------
	Resource* FindNearbyResource(Vector2 v2Location);

private:

	void CreateForests();

	void CreateGoldMines();

	void CreateBerryBushes();

	std::vector<Resource*> m_apResources;

	aie::Texture* m_pTreeTexture;
	aie::Texture* m_pGoldTexture;
	aie::Texture* m_pBerryTexture;

	float m_fTreeAmount;
	float m_fGoldAmount;
	float m_fBerryAmount;


	Floor* m_pFloor;
};

