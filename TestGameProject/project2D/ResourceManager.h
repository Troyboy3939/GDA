#pragma once
#include <vector>
#include "Renderer2D.h"
class Resource;


class ResourceManager
{
public:
	ResourceManager(float fTreeAmount, float fGoldAmount, float fBerryAmount);
	~ResourceManager();

	void Update(float fDeltaTime);

	void Draw(aie::Renderer2D* pRenderer);

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

};

