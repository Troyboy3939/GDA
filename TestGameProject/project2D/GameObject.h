#pragma once

#include "Renderer2D.h"
#include "Vector2.h"

class GameObject
{
public:
	GameObject(Vector2 v2Pos);

	virtual void Update(float fDeltaTime) = 0;


	virtual void Draw(aie::Renderer2D* pRenderer) = 0;

	Vector2 GetPosition();
	void SetPosition(Vector2 v2Pos);
protected:
	Vector2 m_v2Position;

};

