#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Villager.h"
Application2D::Application2D()
{

}

Application2D::~Application2D()
{

}

bool Application2D::startup()
{

	m_2dRenderer = new aie::Renderer2D();



	m_pFont = new aie::Font("./font/consolas.ttf", 12);
	m_timer = 0;

	m_pVillager = new Villager(Vector2(0.0f, 0.0f), true, 10, 10, 10);



	m_pFloor = new Floor(Vector2(300.0f, 100.0f));

	return true;
}

void Application2D::shutdown()
{
	delete m_2dRenderer;
	delete m_pFont;

	if (m_pVillager)
	{
		delete m_pVillager;
	}

	if (m_pFloor)
	{
		delete m_pFloor;
		m_pFloor = nullptr;
	}
}

void Application2D::update(float fDeltaTime)
{

	m_timer += fDeltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * fDeltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * fDeltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * fDeltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * fDeltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_pFloor->Update(fDeltaTime);


}

void Application2D::draw()
{


	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();


	if (m_pVillager)
	{
		m_pVillager->Draw(m_2dRenderer);
	}
	float fX, fY;

	m_2dRenderer->getCameraPos(fX, fY);

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_pFont, fps, fX, 720 - 32 + fY);
	m_2dRenderer->drawText(m_pFont, "Press ESC to quit!", fX, 720 - 64 + fY);

	m_pFloor->Draw(m_2dRenderer);

	// done drawing sprites
	m_2dRenderer->end();
}