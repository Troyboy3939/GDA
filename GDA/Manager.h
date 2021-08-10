#pragma once
#include "Messenger.h"

class GoalBase;


class Manager :
    public Messenger
{
public:

    GoalBase* GetGoal();
private:
    GoalBase* m_pGoal;
};

