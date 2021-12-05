#pragma once
#include "Manager.h"
class MilitaryManager :
    public Manager
{
public:
    MilitaryManager(Blackboard* pBlackboard, Goal* pDefaultGoal = nullptr);
    ~MilitaryManager();


    void SetUpGoals() override;
    void SetUpActions() override;

    void HandleMessage(Message* pMessage) override;

    void Update(float fDeltaTime) override;
private:
};

