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


	//-----------------------------------
	// 	Draw Function -> Called every frame
	//-----------------------------------
	void GetPath(Vector2 v2From, Vector2 v2To, std::vector<Vector2>& rav2Path);

private:
	Vector2 m_v2StartPos;

	aie::Texture* m_pTileTexture;

	std::vector<Tile*> m_apTiles;

	int m_nHeight;
	int m_nWidth;


};

