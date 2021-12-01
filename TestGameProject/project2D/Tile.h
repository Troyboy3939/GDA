#pragma once
#include "Vector2.h"
#include "Texture.h"
#include "Renderer2D.h"
#include <vector>



class Tile
{
public:
	enum class Connection
	{
		Left,
		Right,
		Top,
		Down,
		TopRight,
		TopLeft,
		BottomRight,
		BottomLeft
	};
using Neighbours = std::vector<Tile*>;
	Tile(Vector2 v2Pos, aie::Texture* pTexture);
	~Tile();

	void Update(float fDeltaTime);

	void Draw(aie::Renderer2D* pRenderer);

	void AddNeighbour(Tile* pTile, Connection eCon);

	float GetFScore();
	float GetGScore();
	float GetHScore();

	void SetGScore(float fScore);
	void SetHScore(float fScore);

	Tile* GetPrevious();

	void SetPrevious(Tile* pTile);


	Vector2 GetPosition();


	Neighbours& GetNeighours();

	Tile* GetNeighbour(Connection eTile);

	void Highlight();

	void SetOn(bool bOn);
	bool GetOn();

	aie::Texture* GetTexture();

	bool CanPlaceBuilding();

private:
	Vector2 m_v2Position;
	
	float m_fGScore;
	float m_fHScore;

	Tile* m_pPrevious;

	bool m_bDrawConnection;
	bool m_bDrawGrid;
	bool m_bOn;

	Neighbours m_apNeighbours;




	aie::Texture* m_pTexture;
};


