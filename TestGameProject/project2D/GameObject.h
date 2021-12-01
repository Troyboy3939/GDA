#pragma once

#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>
class Icon;
class Tile;
using Icons = std::vector<Icon*>;


class GameObject
{
public:
	GameObject(Tile* pTile);
	GameObject();
	virtual ~GameObject();

	virtual void Initialise(Tile* pTile);


	virtual void Update(float fDeltaTime) = 0;


	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

	Vector2 GetPosition();
	void SetPosition(Vector2 v2Pos);
protected:
	Vector2 m_v2Position;
	Tile* m_pTile;
};

