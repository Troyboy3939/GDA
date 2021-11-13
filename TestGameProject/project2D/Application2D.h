#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Manager.h"
#include "Floor.h"
#include "ResourceManager.h"

class Empire;
class Villager;
class UnitPool;
class BuildingPool;

class Application2D : public aie::Application
{
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;


	aie::Font* m_pFont;



	Vector2 m_v2Mouse;

	Floor* m_pFloor;
	ResourceManager* m_pResourceManager;
	Empire* m_pPlayer;
	Empire* m_pAI;

	UnitPool* m_pUnitPool;

	BuildingPool* m_pBuildingPool;



	float m_timer;
};