#pragma once
#include "Texture.h"
#include "Renderer2D.h"
#include <vector>
#include "Tile.h"
class Floor
{
public:
	//-----------------------------------
	// 	Constructor
	//-----------------------------------
	Floor(Vector2 v2Pos, int nWidth = 50, int nHeight = 50);
	~Floor();

	//-----------------------------------
	// 	Update function -> Called every frame
	//-----------------------------------
	void Update(float fDeltaTime);


	//-----------------------------------
	// 	Draw Function -> Called every frame
	//-----------------------------------
	void Draw(aie::Renderer2D* pRenderer);

private:
	Vector2 m_v2StartPos;

	aie::Texture* m_pTileTexture;

	std::vector<Tile*> m_apTiles;

	int m_nHeight;
	int m_nWidth;


};

