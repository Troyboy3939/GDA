#include "Action.h"

Action::Action()
{
}

Action::~Action()
{
}

float Action::GetCost()
{
    return m_fCost;
}

std::string Action::GetSatWS()
{
    return m_sSatWorldState;
}

std::vector<std::string> Action::GetReqWS()
{
    return m_asReqWorldState;
}
