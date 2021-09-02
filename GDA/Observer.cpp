#include "Observer.h"

std::unordered_map<std::string, bool>& Observer::GetCurrentWorldState()
{
    return m_CurrentWorldState;
}
