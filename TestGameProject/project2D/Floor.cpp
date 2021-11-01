#include "Floor.h"

Floor::Floor(Vector2 v2Pos, int nWidth, int nHeight)
{
	//calculate number of tiles needed
	auto nTileCount = nWidth * nHeight;
	m_v2StartPos = v2Pos;

	m_nHeight = nHeight;
	m_nWidth = nWidth;

	//reserve that much space to avoid mass resizing
	m_apTiles.reserve(nTileCount);


	m_pTileTexture = new aie::Texture("Textures/Grass.jpg");

	for (int x = 0; x < nWidth; x++)
	{
		for (int y = 0; y < nHeight; y++)
		{
			Vector2 v2Tile = v2Pos;
			v2Tile.x = v2Tile.x + (m_pTileTexture->getWidth() * x);
			v2Tile.y = v2Tile.y + (m_pTileTexture->getHeight() * y);


			m_apTiles.push_back(new Tile(v2Tile,m_pTileTexture));
		}
	}

}

Floor::~Floor()
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			delete m_apTiles[i];
		}
	}

	if (m_pTileTexture)
	{
		delete m_pTileTexture;
		m_pTileTexture = nullptr;
	}

}

void Floor::Update(float fDeltaTime)
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			//Update
			m_apTiles[i]->Update(fDeltaTime);
		}
	}
}

void Floor::Draw(aie::Renderer2D* pRenderer)
{
	for (int i = 0; i < m_apTiles.size(); i++)
	{
		if (m_apTiles[i])
		{
			//Draw
			m_apTiles[i]->Draw(pRenderer);
		}
	}

}
