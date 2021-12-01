#include "Icon.h"
#include "Building.h"
#include "TownCentre.h"
#include "Empire.h"
Icon::Icon(Vector2 v2Position, IType eType)
{
	m_v2Position = v2Position;
	m_eIconType = eType;
	m_bRequiresPlacing = false;

	m_bSelected = false;

	m_fFoodCost = 0.0f;
	m_fWoodCost = 0.0f;
	m_fGoldCost = 0.0f;
	m_bHover = false;

	switch (eType)
	{
	case IType::TownCentre:
	{
		m_pTexture = new aie::Texture("Textures/TCIcon.png");
		m_bRequiresPlacing = true;

		m_sText = "The town centre is one of the most important buildings, as it is where you can create villagers as well as upgrade them";

		m_fFoodCost = 0.0f;
		m_fWoodCost = 300.0f;
		m_fGoldCost = 200.0f;

		m_nRequiredAge = 3;
		break;
	}
	case IType::Storage:
	{
		m_pTexture = new aie::Texture("Textures/StorageIcon.png");
		m_bRequiresPlacing = true;
		m_sText = "The storage building is a building that villagers can place resources inside. It would be beneficial to place these next to where the villagers are collecting resources for a quick drop off time";

		m_fFoodCost = 0.0f;
		m_fWoodCost = 100.0f;
		m_fGoldCost = 0.0f;

		m_nRequiredAge = 1;


		break;
	}
	case IType::Barracks:
	{
		m_pTexture = new aie::Texture("Textures/BarracksIcon.png");
		m_sText = "The barracks is where you can create infantry units.";
		m_bRequiresPlacing = true;

		m_fFoodCost = 0.0f;
		m_fWoodCost = 150.0f;
		m_fGoldCost = 100.0f;


		m_nRequiredAge = 2;
		break;
	}
	case IType::ArcheryRange:
	{
		m_pTexture = new aie::Texture("Textures/ArcheryRangeIcon.png");
		m_sText = "The Archery Range is where you can create ranged units.";
		m_bRequiresPlacing = true;

		m_fFoodCost = 0.0f;
		m_fWoodCost = 150.0f;
		m_fGoldCost = 100.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::Stable:
	{
		m_pTexture = new aie::Texture("Textures/StableIcon.png");
		m_sText = "The Stables are where you can create cavalry units.";
		m_bRequiresPlacing = true;

		m_fFoodCost = 50.0f;
		m_fWoodCost = 150.0f;
		m_fGoldCost = 100.0f;


		m_nRequiredAge = 2;
		break;
	}
	case IType::Villager:
	{
		m_sText = "Villager is the most important unit. Villagers collect resources as well as build the necessary buildings";
		m_pTexture = new aie::Texture("Textures/VillagerIcon.png");

		m_fFoodCost = 50.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 0.0f;

		m_nRequiredAge = 1;
		break;
	}
	case IType::VillSpee:
	{
		m_sText = "This increases the speed of villagers so that they can walk faster";
		m_pTexture = new aie::Texture("Textures/VillagerSpeedIcon.png");

		m_fFoodCost = 100.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 100.0f;

		m_nRequiredAge = 1;
		break;
	}
	case IType::VillInv:
	{
		m_sText = "This increases the inventory of villagers so that they can carry more";
		m_pTexture = new aie::Texture("Textures/VillagerInvIcon.png");

		m_fFoodCost = 0.0f;
		m_fWoodCost = 100.0f;
		m_fGoldCost = 100.0f;

		m_nRequiredAge = 1;
		break;
	}
	case IType::AgeUp:
	{
		m_sText = "This advances your empire to the next age, giving you access to more buildings and units";

		m_pTexture = new aie::Texture("Textures/AgeUpIcon.png");


		m_fFoodCost = 500.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 300.0f;

		m_nRequiredAge = 1;
		break;
	}
	case IType::Swordsman:
	{
		m_sText = "This is a basic infantry unit that is pretty standard against all things";

		m_pTexture = new aie::Texture("Textures/SwordsmanIcon.png");
		m_fFoodCost = 50.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 50.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::Pikeman:
	{
		m_sText = "This is an infantry unit that is pretty effective at killing Cavalry, but is weak to archers";

		m_pTexture = new aie::Texture("Textures/PikemanIcon.png");
		m_fFoodCost = 35.0f;
		m_fWoodCost = 30.0f;
		m_fGoldCost = 35.0f;
		m_nRequiredAge = 2;
	}
		break;
	case IType::InfAtt:
	{
		m_sText = "This increases the attack stat of each infantry unit so that they hit harder";

		m_pTexture = new aie::Texture("Textures/InfAttIcon.png");
		m_fFoodCost = 75.0f;
		m_fWoodCost = 50.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::InfDef:
	{
		m_sText = "This increases the defence stat of each infantry unit so that they are harder to kill";

		m_pTexture = new aie::Texture("Textures/InfDefIcon.png");


		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::InfSpe:
	{
		m_sText = "This increases the speed stat of each infantry unit so that they can walk faster";

		m_pTexture = new aie::Texture("Textures/InfSpeIcon.png");
		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;
		m_nRequiredAge = 2;
		break;
	}
	case IType::Archer:
	{
		m_sText = "This is a basic ranged unit. Effective at killing pikeman, weak at hand to hand combat";

		m_pTexture = new aie::Texture("Textures/ArcherIcon.png");
		m_fFoodCost = 0.0f;
		m_fWoodCost = 50.0f;
		m_fGoldCost = 50.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::Skirmisher:
	{
		m_sText = "This is a ranged unit that is effective at killing other archers, weak at hand to hand combat";

		m_pTexture = new aie::Texture("Textures/SkirmIcon.png");

		m_fFoodCost = 50.0f;
		m_fWoodCost = 50.0f;
		m_fGoldCost = 0.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::ArcAtt:
	{
		m_sText = "This upgrade makes it so that all your ranged units kill faster";

		m_pTexture = new aie::Texture("Textures/ArcherAttIcon.png");

		m_fFoodCost = 75.0f;
		m_fWoodCost = 50.0f;
		m_fGoldCost = 75.0f;


		m_nRequiredAge = 2;
		break;
	}
	case IType::ArcDef:
	{
		m_sText = "This upgrade makes it so that all your ranged units are harder to kill";

		m_pTexture = new aie::Texture("Textures/ArcherDefIcon.png");
		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 2;

		break;
	}
	case IType::ArcSpe:
	{
		m_sText = "This upgrade makes it so that all your ranged units walk faster";

		m_pTexture = new aie::Texture("Textures/ArcherSpeIcon.png");
		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::Scout:
	{
		m_sText = "Basic cavalry unit, effective at hit and run tactics. Weak to pikeman";

		m_pTexture = new aie::Texture("Textures/ScoutIcon.png");
		m_fFoodCost = 75.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 50.0f;

		m_nRequiredAge = 2;
		break;
	}
	case IType::Knight:
	{
		m_sText = "Stronger cavalry unit, effective at hit and run tactics. Weak to pikeman";

		m_pTexture = new aie::Texture("Textures/KnightIcon.png");

		m_fFoodCost = 75.0f;
		m_fWoodCost = 0.0f;
		m_fGoldCost = 100.0f;

		m_nRequiredAge = 3;
		break;
	}
	case IType::CavAtt:
	{
		m_sText = "This upgrade makes it so that all your cavalry units kill faster";

		m_pTexture = new aie::Texture("Textures/CavAttIcon.png");
		m_fFoodCost = 75.0f;
		m_fWoodCost = 50.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 3;
		break;
	}
	case IType::CavDef:
	{
		m_sText = "This upgrade makes it so that all your cavalry units are harder to kill";

		m_pTexture = new aie::Texture("Textures/CavAttIcon.png");

		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 3;
		break;
	}
	case IType::CavSpe:
	{
		m_sText = "This upgrade makes it so that all your cavalry units walk faster";

		m_pTexture = new aie::Texture("Textures/CavSpeIcon.png");

		m_fFoodCost = 50.0f;
		m_fWoodCost = 75.0f;
		m_fGoldCost = 75.0f;

		m_nRequiredAge = 3;
	}
		break;
	default:
		break;
	}

	
}

void Icon::Update(float fDeltaTime)
{
}

void Icon::Draw(aie::Renderer2D* pRenderer, Vector2 v2Camera)
{
	pRenderer->drawSprite(m_pTexture, m_v2Position.x + v2Camera.x, m_v2Position.y + v2Camera.y, 0.0f, 0.0f, 0.0f, 2.0f);

	pRenderer->setRenderColour(1.0f,1.0f,1.0f);
	if (m_bSelected)
	{

		pRenderer->drawSprite(m_pTexture, 781.0f + v2Camera.x, 175.0f + v2Camera.y, 0.0f, 0.0f, 0.0f, 2.0f);
	}

	if (m_bHover)
	{
		pRenderer->drawSprite(m_pTexture, 478.0f + v2Camera.x, 174.0f + v2Camera.y, 0.0f, 0.0f, 0.0f, 2.0f);
	}
}

void Icon::SetPosition(Vector2 v2Position)
{
	m_v2Position = v2Position;
}

Vector2 Icon::GetPosition()
{
	return m_v2Position;
}

void Icon::Press(Building* pBuilding)
{

	if (pBuilding)
	{
		if (m_eIconType == IType::AgeUp && pBuilding->GetTeam()->GetAge() >= 3)
		{
			return;
		}

		pBuilding->AddActionToQueue(this);
	}
}

bool Icon::GetRequiresPlacing()
{
	return m_bRequiresPlacing;
}

Icon::IType Icon::GetIconType()
{
	return m_eIconType;
}

void Icon::SetSelected(bool bSelected)
{
	m_bSelected = bSelected;
}

bool Icon::CheckMouseHover(Vector2 v2Mouse)
{
	if (v2Mouse.x > m_v2Position.x - 32 && v2Mouse.x < m_v2Position.x + 32)
	{
		if (v2Mouse.y > m_v2Position.y - 32 && v2Mouse.y < m_v2Position.y + 32)
		{
			m_bHover = true;
			return true;
		}

	}

	m_bHover = false;

	return false;
}

std::string& Icon::GetText()
{
	return m_sText;
}

float Icon::GetGoldCost()
{
	return m_fGoldCost;
}

float Icon::GetWoodCost()
{
	return m_fWoodCost;
}

float Icon::GetFoodCost()
{
	return m_fFoodCost;
}

int Icon::GetRequiredAge()
{
	return m_nRequiredAge;
}
