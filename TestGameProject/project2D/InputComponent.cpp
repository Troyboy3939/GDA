#include "InputComponent.h"

InputComponent::InputComponent(Empire* pTeam)
{
	m_pTeam = pTeam;

}

Empire* InputComponent::GetTeam()
{
	return m_pTeam;
}
