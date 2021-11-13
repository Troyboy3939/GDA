#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Villager.h"
#include "Empire.h"
#include "UnitPool.h"
#include "BuildingPool.h"
#include <time.h>
Application2D::Application2D()
{

}

Application2D::~Application2D()
{

}

bool Application2D::startup()
{
	srand(time(NULL));
	
	m_2dRenderer = new aie::Renderer2D();


	
	m_pFont = new aie::Font("Fonts/consolas.ttf", 24);
	m_timer = 0;

	
	m_pFloor = new Floor(Vector2(0.0f, 0.0f),75,75);

	m_pResourceManager = new ResourceManager(100,400,400);



	m_pUnitPool = new UnitPool(30);
	m_pBuildingPool = new BuildingPool(5);

	Vector3 v3StartingResources(200,200,200);

	m_pPlayer = new Empire(m_pBuildingPool,m_pUnitPool,m_pFloor,m_pResourceManager,Vector2(700,300),Vector3(0.0f,0.0f,1.0f), v3StartingResources);

	m_pAI = new Empire(m_pBuildingPool, m_pUnitPool, m_pFloor, m_pResourceManager, Vector2(3750,3900), Vector3(1.0f, 0.0f, 0.0f), v3StartingResources, true);
	

	return true;
}

void Application2D::shutdown()
{
	delete m_2dRenderer;
	delete m_pFont;

	

	if (m_pFloor)
	{
		delete m_pFloor;
		m_pFloor = nullptr;
	}

	if (m_pResourceManager)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pUnitPool)
	{
		delete m_pUnitPool;
		m_pUnitPool = nullptr;
	}
	if (m_pBuildingPool)
	{
		delete m_pBuildingPool;
		m_pBuildingPool = nullptr;
	}

	if (m_pPlayer)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pAI)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}
}

void Application2D::update(float fDeltaTime)
{

	m_timer += fDeltaTime;

	// input example
	auto pInput = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float fCamPosX;
	float fCamPosY;
	m_2dRenderer->getCameraPos(fCamPosX, fCamPosY);

	if (pInput->isKeyDown(aie::INPUT_KEY_UP))
		fCamPosY += 500.0f * fDeltaTime;

	if (pInput->isKeyDown(aie::INPUT_KEY_DOWN))
		fCamPosY -= 500.0f * fDeltaTime;

	if (pInput->isKeyDown(aie::INPUT_KEY_LEFT))
		fCamPosX -= 500.0f * fDeltaTime;

	if (pInput->isKeyDown(aie::INPUT_KEY_RIGHT))
		fCamPosX += 500.0f * fDeltaTime;

	m_2dRenderer->setCameraPos(fCamPosX, fCamPosY);

	// exit the application
	if (pInput->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_pFloor->Update(fDeltaTime);

	m_pPlayer->Update(fDeltaTime);
	m_pAI->Update(fDeltaTime);


	m_v2Mouse.x = pInput->getMouseX() + fCamPosX;
	m_v2Mouse.y = pInput->getMouseY() + fCamPosY;

	m_pResourceManager->Update(fDeltaTime);
}

void Application2D::draw()
{


	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	float fX, fY;

	m_2dRenderer->getCameraPos(fX, fY);

	
	

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_pFont, fps, fX, 720 - 32 + fY,0.0f);
	m_2dRenderer->drawText(m_pFont, "Press ESC to quit!", fX, 720 - 64 + fY, 0.0f);

	char szMX[32];
	sprintf_s(szMX, 32, "Mouse X: %f", m_v2Mouse.x);
	m_2dRenderer->drawText(m_pFont, szMX, fX, 720 - 128 + fY, 0.0f);

	char szMY[32];
	sprintf_s(szMY, 32, "Mouse Y: %f", m_v2Mouse.y);
	m_2dRenderer->drawText(m_pFont, szMY, fX, 720 - 200 + fY, 0.0f);




	m_pFloor->Draw(m_2dRenderer);
	m_pAI->Draw(m_2dRenderer);
	m_pPlayer->Draw(m_2dRenderer);


	m_pResourceManager->Draw(m_2dRenderer);

	

	// done drawing sprites
	m_2dRenderer->end();
}