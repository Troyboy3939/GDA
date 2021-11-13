#pragma once
#include "Vector2.h"
#include "Texture.h"
#include "Renderer2D.h"
#include <vector>



class Tile
{
public:
using Neighbours = std::vector<Tile*>;
	Tile(Vector2 v2Pos, aie::Texture* pTexture);
	~Tile();

	void Update(float fDeltaTime);

	void Draw(aie::Renderer2D* pRenderer);

	void AddNeighbour(Tile* pTile);

	float GetFScore();
	float GetGScore();
	float GetHScore();

	void SetGScore(float fScore);
	void SetHScore(float fScore);

	Tile* GetPrevious();

	void SetPrevious(Tile* pTile);


	Vector2 GetPosition();


	Neighbours& GetNeighours();

	void Highlight();
private:
	Vector2 m_v2Position;
	
	float m_fGScore;
	float m_fHScore;

	Tile* m_pPrevious;

	bool m_bDrawConnection;
	bool m_bDrawGrid;

	Neighbours m_apNeighbours;




	aie::Texture* m_pTexture;
};


