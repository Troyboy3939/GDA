#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include "Font.h"
#include "Unit.h"
class PlayerComponent;
class Empire;
class UI
{
public:
	UI(Empire* pTeam, PlayerComponent* pPlayer);
	~UI();
	void Update(float fDeltaTime, Vector2 v2Mouse);

	void Draw(aie::Renderer2D* pRenderer, Vector2 v2CameraLocation);

	Icon* CheckIfIconClicked(Vector2 v2Mouse);

	Icon* PressIcon(int nIconNumber);
	Icon* PressIfAble(int nIconNumber);

	void ClearHover();

private:
	void SetUpIcons();

	
	aie::Texture* m_pTexture;
	aie::Font* m_pResourceFont;
	aie::Font* m_pDescriptionFont;

	Vector2 m_v2Mouse;
	Vector2 m_v2Camera;

	Empire* m_pTeam;
	PlayerComponent* m_pPlayer;

	//multi-dimensional array for storing Icons of different things
	std::vector<Icons> m_aaIcons;

	int m_nCurrentSelections;


};

