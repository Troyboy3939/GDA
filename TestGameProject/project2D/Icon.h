#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Vector2.h"
#include <string>


class Building;
class Icon
{
public:
	enum class IType
	{
		TownCentre,
		Storage,
		Barracks,
		ArcheryRange,
		Stable,
		Villager,
		VillSpee,
		VillInv,
		AgeUp,
		Swordsman,
		Pikeman,
		InfAtt,
		InfDef,
		InfSpe,
		Archer,
		Skirmisher,
		ArcAtt,
		ArcDef,
		ArcSpe,
		Scout,
		Knight,
		CavAtt,
		CavDef,
		CavSpe

	};



	Icon(Vector2 v2Position, IType eType);

	void Update(float fDeltaTime);

	void Draw(aie::Renderer2D* pRenderer, Vector2 v2Camera);

	void SetPosition(Vector2 v2Position);

	Vector2 GetPosition();

	void Press(Building* pBuilding);

	bool GetRequiresPlacing();

	IType GetIconType();

	void SetSelected(bool bSelected);

	bool CheckMouseHover(Vector2 v2Mouse);

	std::string& GetText();

	float GetGoldCost();
	float GetWoodCost();
	float GetFoodCost();


	int GetRequiredAge();
private:
	aie::Texture* m_pTexture;

	IType m_eIconType;

	bool m_bSelected;
	bool m_bHover;

	Vector2 m_v2Position;


	bool m_bRequiresPlacing;

	std::string m_sText;


	float m_fGoldCost;
	float m_fWoodCost;
	float m_fFoodCost;

	int m_nRequiredAge;

};

