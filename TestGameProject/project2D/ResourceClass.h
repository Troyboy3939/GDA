#pragma once
#include "GameObject.h"
#include "Texture.h"
//forward Declaration
class Villager;

//--------------------
//  Abstract Class for 
//--------------------
class Resource : GameObject
{
public:
	enum class Type
	{
		WOOD,
		GOLD,
		FOOD
	};

	Resource(float fAmountOfResources, Type eType, Vector2 v2Position, aie::Texture* pTexture = nullptr);
	

	void Update(float fDeltaTime);


	void Draw(aie::Renderer2D* pRenderer);

	Type GetType();
	void SetType(Type eType);

	void Collect(float fAmount);

	float GetResourcesLeft();

private:

	float m_fResourcesLeft;
	Type m_eType;

	aie::Texture* m_pTexture;

};

