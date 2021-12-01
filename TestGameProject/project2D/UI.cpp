#include "UI.h"
#include "Empire.h"
#include "PlayerComponent.h"
#include <cmath>
#include "Icon.h"
#include "Building.h"

UI::UI(Empire* pTeam, PlayerComponent* pPlayer)
{
	m_pTexture = new aie::Texture("Textures/UI.png");
	m_pResourceFont = new aie::Font("Fonts/consolas.ttf", 24);
	m_pDescriptionFont = new aie::Font("Fonts/consolas.ttf", 12);
	m_pTeam = pTeam;
	m_pPlayer = pPlayer;

	SetUpIcons();



}

UI::~UI()
{

	//delete every icon

	//for every column in 2D array
	for (auto& rapIcons : m_aaIcons)
	{
		//check every element
		for (auto pIcon : rapIcons)
		{
	
			//and delete it if it exists
			if (pIcon)
			{
				delete pIcon;
			}
		}
	}
}

void UI::Update(float fDeltaTime, Vector2 v2Mouse)
{
	m_v2Mouse = v2Mouse;

	auto& rapSelected = m_pPlayer->GetSelectedUnits();

	auto bVillager = false;


	//Check if every selected unit is a villager
	for (int i = 0; i < rapSelected.size(); i++)
	{
		if (rapSelected[i])
		{
			if (rapSelected[i]->GetUnitType() == Unit::UType::Villager)
			{
				bVillager = true;
			}
			else
			{
				bVillager = false;
				break;
			}
		}
	}

	//Get a pointer to the building that is currently selected
	auto pBuilding = m_pPlayer->GetSelectedBuilding();



	//if only villagers are selected
	if (bVillager)
	{
		//vilager takes place of storage with icons
		m_nCurrentSelections = static_cast<int>(Building::BType::Storage);
	} //if a building other than storage is selected
	else if (pBuilding && pBuilding->GetBuildingType() != Building::BType::Storage && pBuilding->GetBuildingType() != Building::BType::NoTypes)
	{
		m_nCurrentSelections = static_cast<int>(pBuilding->GetBuildingType());
	}
	else
	{
		m_nCurrentSelections = -1;
	}

}

void UI::Draw(aie::Renderer2D* pRenderer, Vector2 v2CameraLocation)
{
	m_v2Camera = v2CameraLocation;


	//draw the UI sprite
	pRenderer->drawSprite(m_pTexture, v2CameraLocation.x + 960, v2CameraLocation.y + 125, 0.0f, 0.0f, 0.0f, 2.0f);




	auto pBuilding = m_pPlayer->GetSelectedBuilding();

	Icon* pAction = nullptr;

	//if a building has been selected, then we need to set up the progress bar for anything 
	//that it might be creating such as a villager or an upgrade
	if (pBuilding)
	{
		pAction = pBuilding->GetCurrentAction();

		auto fProgress = pBuilding->GetProgress();

		if (pAction)
		{
			//Set selected -> this will make so that it will draw again at the description
			pAction->SetSelected(true);

			pRenderer->setRenderColour(203.0f / 255.0f, 155.0f / 255.0f, 129.0f / 255.0f);

			pRenderer->drawCircle(741.0f + m_v2Camera.x,81.0f + m_v2Camera.y,10);


			auto fX = Vector2::Lerp(741.0f,904.0f, fProgress);

			pRenderer->drawLine(741.0f + m_v2Camera.x,81.0f + m_v2Camera.y,fX + m_v2Camera.x, 81.0f + m_v2Camera.y,12.0f);


			pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);


			if (pBuilding->GetActionsLeft() > 1)
			{
				pRenderer->setRenderColour(0.0f,0.0f,0.0f);
				char szQueueLength[32];
				sprintf_s(szQueueLength, 32, "Remaining: %i", static_cast<int>(pBuilding->GetActionsLeft() - 1));

				pRenderer->drawText(m_pDescriptionFont, szQueueLength, 831.0f + m_v2Camera.x, 140.0f + m_v2Camera.y);
				pRenderer->setRenderColour(1.0f,1.0f,1.0f);
			}

		}
	}

	
	
	Icon* pHover = nullptr;

	//draw every icon
	if (m_nCurrentSelections >= 0 && m_nCurrentSelections < m_aaIcons.size())
	{
		for (auto pIcon : m_aaIcons[m_nCurrentSelections])
		{
			//if mouse is on UI
			if (m_v2Mouse.y < 250.0f)
			{
				if (pIcon->CheckMouseHover(m_v2Mouse))
				{
					pHover = pIcon;
				}
			}
			


			//if you meet the requirements
			if (!m_pTeam->CanPerformAction(pIcon,false))
			{
				pRenderer->setRenderColour(0.329f, 0.329f, 0.329f);
			}

			pIcon->Draw(pRenderer, v2CameraLocation);


			pRenderer->setRenderColour(1.0f, 1.0f, 1.0f);


			
		}
	}


	//Draw information about icon currently hovered over
	if (pHover)
	{
		//Get the description o the icon
		auto& rsText = pHover->GetText();

		//make the text black so that it is easier to read
		pRenderer->setRenderColour(0.0f,0.0f,0.0f);

		//divide the length of the texy by 28 (roughly how many characters per line) then then draw text that many times
		for (int i = 0; i < ceilf( rsText.length() / 28.0f); i++)
		{
			//draw the 28 segment long pieces of text
			pRenderer->drawText(m_pDescriptionFont, rsText.substr((i) * 28, 28).c_str(),447.0f + m_v2Camera.x, 121.0f + m_v2Camera.y - (15 * i));
		}

		//Create the necessary text
		char szWood[32];
		sprintf_s(szWood, 32, "Wood: %i", static_cast<int>(pHover->GetWoodCost()));

		char szFood[32];
		sprintf_s(szFood, 32, "Food: %i", static_cast<int>(pHover->GetFoodCost()));

		char szGold[32];
		sprintf_s(szGold, 32, "Gold: %i", static_cast<int>(pHover->GetGoldCost()));


		pRenderer->drawText(m_pDescriptionFont,szWood, 524.0f + m_v2Camera.x, 195.0f + m_v2Camera.y);
		pRenderer->drawText(m_pDescriptionFont,szFood, 524.0f + m_v2Camera.x, 183.0f + m_v2Camera.y);
		pRenderer->drawText(m_pDescriptionFont,szGold, 524.0f + m_v2Camera.x, 171.0f + m_v2Camera.y);
		
		

		pRenderer->setRenderColour(1.0f,1.0f,1.0f);
	}
	

	if (pAction)
	{
		pAction->SetSelected(false);
	}


	
	//Create the necessary text
	char szWood[32];
	sprintf_s(szWood, 32, "Wood: %i", static_cast<int>(m_pTeam->GetWood()));

	char szFood[32];
	sprintf_s(szFood, 32, "Food: %i", static_cast<int>(m_pTeam->GetFood()));
	
	char szGold[32];
	sprintf_s(szGold, 32, "Gold: %i", static_cast<int>(m_pTeam->GetGold()));

	//Update the amount of resources the player has on the UI
	pRenderer->setRenderColour(0.0f,0.0f,0.0f);
	pRenderer->drawText(m_pResourceFont, szWood, 1088.0f + m_v2Camera.x,187 + m_v2Camera.y);
	pRenderer->drawText(m_pResourceFont, szFood, 1088.0f + m_v2Camera.x,140 + m_v2Camera.y);
	pRenderer->drawText(m_pResourceFont, szGold, 1088.0f + m_v2Camera.x,90 + m_v2Camera.y);
	pRenderer->setRenderColour(1.0f,1.0f,1.0f);


}

Icon* UI::CheckIfIconClicked(Vector2 v2Mouse)
{

	if (m_nCurrentSelections > -1 && m_nCurrentSelections < m_aaIcons.size())
	{
		for (int i = 0; i < m_aaIcons[m_nCurrentSelections].size(); i++)
		{

			auto pIcon = m_aaIcons[m_nCurrentSelections][i];

			if (pIcon)
			{
				auto v2IconPos = pIcon->GetPosition();

				//if x is within the bounds
				if (v2Mouse.x > v2IconPos.x - 32 && v2Mouse.x < v2IconPos.x + 32)
				{
					if (v2Mouse.y > v2IconPos.y - 32 && v2Mouse.y < v2IconPos.y + 32)
					{
						
						return PressIfAble(i);
						
					}
				}
			}

		}
	}


	return nullptr;
}

Icon* UI::PressIcon(int nIconNumber)
{
	if (m_nCurrentSelections > -1 && m_nCurrentSelections < m_aaIcons.size())
	{
		auto& rapIcons = m_aaIcons[m_nCurrentSelections];

		if (nIconNumber > -1 && nIconNumber < rapIcons.size())
		{
			rapIcons[nIconNumber]->Press(m_pPlayer->GetSelectedBuilding());

			return rapIcons[nIconNumber];
		}
	}

	return nullptr;
}



Icon* UI::PressIfAble(int nIconNumber)
{
	if (m_nCurrentSelections > -1 && m_nCurrentSelections < m_aaIcons.size())
	{

		auto pIcon = m_aaIcons[m_nCurrentSelections][nIconNumber];

		if (!pIcon->GetRequiresPlacing())
		{
			if (m_pTeam->CanPerformAction(pIcon))
			{
				m_pTeam->SpendResources(Vector3(pIcon->GetWoodCost(), pIcon->GetFoodCost(), pIcon->GetGoldCost()));

				return PressIcon(nIconNumber);
			}
		}
		else
		{
			return PressIcon(nIconNumber);
		}
	}



	return nullptr;
}

void UI::ClearHover()
{
	
}

void UI::SetUpIcons()
{
	m_nCurrentSelections = -1;

	
	//set up Icons for these
	Icons viSelect;

	//Villager can create every one of the buildings
	for (int i = 0; i < static_cast<int>(Building::BType::NoTypes); i++)
	{
		//count how many times this can be divided by 3 -> that tells us the Y
		auto nY = static_cast<int>(i / 3.0f);
		int nX = i - (nY * 3);
	
	
		viSelect.push_back(new Icon(Vector2(183.0f + nX * 69,197.0f - nY * 69),static_cast<Icon::IType>(i)));
	}

	Icons tcSelect;


	//start at 5 being Icon::Villager == 5 and the next 4 and the needed icons for TC
	for (int i = 5; i < 9; i++)
	{
		//count how many times this can be divided by 3 -> that tells us the Y
		auto nY = static_cast<int>((i - 5)/ 3.0f);
		int nX = (i - 5) - (nY * 3);


		tcSelect.push_back(new Icon(Vector2(183.0f + nX * 69, 197.0f - nY * 69), static_cast<Icon::IType>(i)));
	}
	
	Icons arSelect;
	for (int i = 14; i < 19; i++)
	{
		//count how many times this can be divided by 3 -> that tells us the Y
		auto nY = static_cast<int>((i - 14) / 3.0f);
		int nX = (i - 14) - (nY * 3);


		arSelect.push_back(new Icon(Vector2(183.0f + nX * 69, 197.0f - nY * 69), static_cast<Icon::IType>(i)));
	}



	Icons baSelect;
	for (int i = 9; i < 14; i++)
	{
		//count how many times this can be divided by 3 -> that tells us the Y
		auto nY = static_cast<int>((i - 9) / 3.0f);
		int nX = (i - 9) - (nY * 3);


		baSelect.push_back(new Icon(Vector2(183.0f + nX * 69, 197.0f - nY * 69), static_cast<Icon::IType>(i)));
	}

	Icons stSelect;
	for (int i = 19; i < 23; i++)
	{
		//count how many times this can be divided by 3 -> that tells us the Y
		auto nY = static_cast<int>((i - 19) / 3.0f);
		int nX = (i - 19) - (nY * 3);


		stSelect.push_back(new Icon(Vector2(183.0f + nX * 69, 197.0f - nY * 69), static_cast<Icon::IType>(i)));
	}

	//In order of the Building with villager replacing the storage since it doesn't need one
	m_aaIcons.push_back(tcSelect);
	m_aaIcons.push_back(viSelect);
	m_aaIcons.push_back(baSelect);
	m_aaIcons.push_back(arSelect);
	m_aaIcons.push_back(stSelect);


}

	
