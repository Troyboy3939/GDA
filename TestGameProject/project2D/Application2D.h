#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Manager.h"


class Villager;
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

	Villager* m_pVillager;

	aie::Font* m_pFont;

	float m_timer;
};