#include "PlayerComponent.h"
#include "Empire.h"
#include "Unit.h"
#include "ResourceManager.h"
#include "Villager.h"
#include "UI.h"
#include "Icon.h"
#include "Building.h"
#include "Swordsman.h"
#include "Pikeman.h"
#include "Scout.h"
#include "Knight.h"
#include "Archer.h"
#include "Skirmisher.h"
#include "BuildingPool.h"
#include "UnitPool.h"

PlayerComponent::PlayerComponent(Empire* pTeam) : InputComponent(pTeam)
{
	//Get a reference to the input
	m_pInput = aie::Input::getInstance();

	//Set up the speed that the camera moves at
	m_fCameraSpeed = 500;

	//store deltatime so that it can be used outside of update function
	m_fDeltaTime = 0.0f;

	//Timer to store how long the mouse button has been pressed for -1 means not on, > 0.0f == on
	m_fHoldTimer - 1.0f;

	//when the left mouse button has been pressed/released
	m_bMousePressed = false;
	m_bMouseReleased = false;

	//initialise the UI
	m_pUI = new UI(m_pTeam,this);
	m_pIcon = nullptr;

	m_bPlaced = false;
	m_pSelectedBuilding = nullptr;
}

PlayerComponent::~PlayerComponent()
{
	if (m_pUI)
	{
		delete m_pUI;
		m_pUI = nullptr;
	}

}

void PlayerComponent::Update(float fDeltaTime)
{
	//if timer has been activated
	if (m_fHoldTimer >= 0.0f)
	{
		m_fHoldTimer += fDeltaTime;
	}

	//Check whether keys / mouse buttons have been pressed
	UpdateInputs(fDeltaTime);
	
	//update the UI
	m_pUI->Update(fDeltaTime,m_v2Mouse);

}

void PlayerComponent::Draw(aie::Renderer2D* pRenderer)
{
	//Move the camera accordingly
	UpdateCamera(pRenderer);

	//draw the UI 
	m_pUI->Draw(pRenderer, m_v2CameraPos);

	//for every selected unit, draw a ring around them
	for (int i = 0; i < m_apSelectedUnits.size(); i++)
	{
		if (m_apSelectedUnits[i])
		{
			pRenderer->setRenderColour(0.0f, 1.0f, 0.0f);
			pRenderer->drawCircle(m_apSelectedUnits[i]->GetPosition().x, m_apSelectedUnits[i]->GetPosition().y, m_apSelectedUnits[i]->GetRadius() + 5, 99.0f);
			pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
		}
	}
}

Units& PlayerComponent::GetSelectedUnits()
{
	return m_apSelectedUnits;
}

Building* PlayerComponent::GetSelectedBuilding()
{
	return m_pSelectedBuilding;
}

void PlayerComponent::PlaceBuilding(int nBuildingType)
{

	for (int i = 0; i < m_apSelectedUnits.size(); i++)
	{
		auto pUnit = m_apSelectedUnits[i];

		//if the unit is a villager,
		if (pUnit && pUnit->GetUnitType() == Unit::UType::Villager)
		{

			//if there is a building where the mouse is
			if (!m_pIcon)
			{

				//cast it to a villager
				auto pVil = static_cast<Villager*>(pUnit);

				pVil->HelpBuild(static_cast<Building::BType>(nBuildingType), m_v2Mouse + m_v2CameraPos);

				m_pIcon = nullptr;
			}
			else
			{
				//cast it to a villager
				auto pVil = static_cast<Villager*>(pUnit);

				pVil->CreateBuilding(static_cast<Building::BType>(nBuildingType), m_v2Mouse + m_v2CameraPos);

				m_pIcon = nullptr;
			}


			

		}
	}

}

void PlayerComponent::VillagerRightClick(Vector2 v2Location)
{
	auto pResourceMan = m_pTeam->GetResourceManager();


	auto pResource = pResourceMan->GetResourceAtLocation(v2Location);
	

	auto pBuilding = m_pTeam->GetBuildingAtLocation(v2Location);

	if (pResource)
	{
		for (int i = 0; i < m_apSelectedUnits.size(); i++)
		{
			if (m_apSelectedUnits[i])
			{

				auto eUnitType = m_apSelectedUnits[i]->GetUnitType();

				if (eUnitType == Unit::UType::Villager)
				{
					auto pVillager = dynamic_cast<Villager*>(m_apSelectedUnits[i]);

					pVillager->StartCollectingResource(pResource);
				}

			}

			
		}
	}
	else if (pBuilding)
	{
		PlaceBuilding(static_cast<int>(pBuilding->GetBuildingType()));
	}
	else if(!m_bPlaced)
	{
		MilitaryRightClick(v2Location);
	}

	m_bPlaced = false;
}

void PlayerComponent::MilitaryRightClick(Vector2 v2Location)
{
	//------------------
	// Attack unit
	//------------------
	auto pBuildPool = m_pTeam->GetBuildPool();


	auto pBuilding = pBuildPool->GetBuildingAtLocation(v2Location);

	auto pUnitPool = m_pTeam->GetUnitPool();


	auto pSelectedUnit = pUnitPool->GetUnitAtLocation(v2Location);
	
	for (auto pUnit : m_apSelectedUnits)
	{
		if (pUnit)
		{
			auto& rapGroup = pUnit->GetGroup();

			rapGroup.clear();

			rapGroup.insert(rapGroup.end(), m_apSelectedUnits.begin(), m_apSelectedUnits.end());

			pUnit->MoveTo(m_v2Mouse + m_v2CameraPos);

			if (pUnit->GetUnitType() == Unit::UType::Villager)
			{
				static_cast<Villager*>(pUnit)->SetIdle();
			}
			else
			{
				if (pBuilding && pBuilding->GetTeam() != m_pTeam)
				{
					static_cast<MilitaryUnit*>(pUnit)->AttackBuilding(pBuilding);
				}
				else if (pSelectedUnit && pSelectedUnit->GetTeam() != m_pTeam)
				{
					static_cast<MilitaryUnit*>(pUnit)->AttackUnit(pSelectedUnit);
				}
				else
				{
					static_cast<MilitaryUnit*>(pUnit)->Idle();
				}
			}
		}
	}
	


	
}

void PlayerComponent::UpdateInputs(float fDeltaTime)
{





	m_fDeltaTime = fDeltaTime;

	auto& ranKeys = m_pInput->getPressedCharacters();



	auto bPressedKey = false;
	for (int i = 0; i < ranKeys.size(); i++)
	{
		switch (static_cast<aie::EInputCodes>(ranKeys[i]))
		{
			case 'w':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(1);
				break;
			}
			case 'a':
			{
				bPressedKey = true;
				m_pIcon =  m_pUI->PressIfAble(3);
				break;
			}
			case 's':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(4);
				break;
			}
			case 'd':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(5);
				break;
			}
			case 'q':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(0);
				break;
			}
			case 'e':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(2);
				break;
			}
			case 'z':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(6);
				break;
			}
			case 'x':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(7);
				break;
			}
			case 'c':
			{
				bPressedKey = true;
				m_pIcon = m_pUI->PressIfAble(8);
				break;
			}
		}

	}

	m_bMousePressed = m_pInput->wasMouseButtonPressed(0);
	m_bMouseReleased = m_pInput->wasMouseButtonReleased(0);

	


	if (m_bMousePressed && !bPressedKey)
	{
		if (m_v2Mouse.y > 250)
		{
			m_apSelectedUnits.clear();

			m_pSelectedBuilding = nullptr;

			m_pIcon = nullptr;

			//location of where mouse was pressed
			m_v2PressedLocation = m_v2CameraPos + m_v2Mouse;
			m_fHoldTimer = 0.0f;
		}
	}

	

	if (m_bMouseReleased && !bPressedKey)
	{
		m_v2ReleasedLocation = m_v2CameraPos + m_v2Mouse;
		if (m_fHoldTimer < 0.2f)
		{
			//mouse press
			if (m_v2Mouse.y <= 250) //if less than that the user will be clicking on the UI
			{
				m_pIcon = m_pUI->CheckIfIconClicked(m_v2Mouse);

			}
			else  //else they have release it somewhere else
			{
				m_pIcon = nullptr;
				
				Vector2 v2Location = m_v2Mouse + m_v2CameraPos;
				m_apSelectedUnits.push_back(m_pTeam->GetUnitAtLocation(v2Location));

				if (m_apSelectedUnits.size() == 1 && !m_apSelectedUnits[0])
				{
					//now check if it was a building
					auto pBuilding = m_pTeam->GetBuildingAtLocation(m_v2Mouse + m_v2CameraPos);

					//if it was a building
					if (pBuilding)
					{
						if (pBuilding->GetPercentageComplete() >= 100.0f)
						{
							m_pSelectedBuilding = pBuilding;
						}

					}
				}
			}
		
		

		}
		else if(!m_pIcon && m_fHoldTimer >= 0.2f)
		{
			//hold

			Vector2 v2PressedToReleased = m_v2PressedLocation - m_v2ReleasedLocation;

			m_pTeam->GetUnitsWithBounds(m_v2PressedLocation,m_v2ReleasedLocation,m_apSelectedUnits);

		}


		m_v2PressedLocation.x = 0.0f;
		m_v2PressedLocation.y = 0.0f;

		m_fHoldTimer = -1.0f;
	}

	if (m_pInput->wasMouseButtonReleased(aie::EInputCodes::INPUT_MOUSE_BUTTON_RIGHT))
	{


		//--------------------------------
		// Check if clicking on resource
		//--------------------------------

		if (m_pIcon)
		{
			if (m_pIcon->GetRequiresPlacing())
			{
				PlaceBuilding(static_cast<int>(m_pIcon->GetIconType()));
			}
			else
			{


				m_pIcon->Press(m_pSelectedBuilding);
			}
		}


		if (m_apSelectedUnits.size() > 0)
		{

			if (m_apSelectedUnits[0])
			{
				if (m_apSelectedUnits[0]->GetUnitType() == Unit::UType::Villager )
				{
					VillagerRightClick(m_v2Mouse + m_v2CameraPos);
				}
				else
				{
					MilitaryRightClick(m_v2Mouse + m_v2CameraPos);
				}
			}
		}
	}
	
	//update mouse position
	m_v2Mouse.x = m_pInput->getMouseX();
	m_v2Mouse.y = m_pInput->getMouseY();


}

void PlayerComponent::UpdateCamera(aie::Renderer2D* pRenderer)
{
	float fX;
	float fY;

	pRenderer->getCameraPos(fX, fY);


	//Move camera based on mouse position
	if (m_v2Mouse.x < 100.0f)
	{

		fX -= m_fCameraSpeed * m_fDeltaTime;

		if (fX < -19.0f)
		{
			fX = -19.0f;
		}
	}
	else if (m_v2Mouse.x > 1750.0f && m_v2Mouse.x < 1910)
	{
		fX += m_fCameraSpeed * m_fDeltaTime;
		if (fX > 2832.0f)
		{
			fX = 2832.0f;
		}
	}

	if (m_v2Mouse.y > 870.0f)
	{
			fY += m_fCameraSpeed * m_fDeltaTime;
		if (fY > 3766.0f)
		{
			fY = 3766.0f;
		}
	}
	else if (m_v2Mouse.y < 100.0f)
	{
		fY -= m_fCameraSpeed * m_fDeltaTime;
		if (fY < -128.0f)
		{
			fY = -128.0f;
		}
	}

	//Set the camera position so this can be used in the update
	pRenderer->setCameraPos(fX, fY);
	m_v2CameraPos.x = fX;
	m_v2CameraPos.y = fY;



	if (!m_v2PressedLocation.isZero())
	{
		pRenderer->drawLine(m_v2PressedLocation.x, m_v2PressedLocation.y, m_v2Mouse.x + fX, m_v2PressedLocation.y);
		pRenderer->drawLine(m_v2PressedLocation.x, m_v2PressedLocation.y, m_v2PressedLocation.x, m_v2Mouse.y + fY);
		pRenderer->drawLine(m_v2Mouse.x + fX, m_v2Mouse.y + fY, m_v2PressedLocation.x, m_v2Mouse.y + fY);
		pRenderer->drawLine(m_v2Mouse.x + fX, m_v2Mouse.y + fY, m_v2Mouse.x + fX, m_v2PressedLocation.y);


		//pRenderer->drawLine(m_v2PressedLocation.x, m_v2PressedLocation.y, m_v2Mouse.x + fX, m_v2Mouse.y + fY);
	}

}
