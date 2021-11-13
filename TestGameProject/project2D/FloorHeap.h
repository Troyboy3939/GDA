#pragma once
#include <vector>

class Tile;


class FloorHeap
{
public:

	

	FloorHeap();
	~FloorHeap();


	Tile* GetTop();
	int Size();
	void Clear();
	void Add(Tile* pTile);
	bool Find(Tile* pTile);
private:


	int GetChild(int nIndex, int nChild);
	int GetParent(int nIndex);
	std::vector<Tile*> m_aTiles;
};

