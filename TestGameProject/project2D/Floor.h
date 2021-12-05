#pragma once
#include "Texture.h"
#include "Renderer2D.h"
#include <deque>
#include "Tile.h"
#include <unordered_map>

class FloorHeap;

using Path = std::deque<Vector2>;

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
	void GetPath(Vector2 v2From, Vector2 v2To, Path& rav2Path);

	//-----------------------------------
	// 	Returns a tile for a given position
	//-----------------------------------
	Tile* PosToTile(Vector2 v2Position);


	//-----------------------------------
	// 	Tells you whether you can building
	// 	something at this location
	//-----------------------------------
	bool CanBuildAt(Vector2 v2Position);
private:
	Vector2 m_v2StartPos;

	aie::Texture* m_pTileTexture;

	std::vector<Tile*> m_apTiles;

	int m_nHeight;
	int m_nWidth;

	FloorHeap* m_pOpenList;
	std::unordered_map<Tile*, bool> m_aClosedList;

};

