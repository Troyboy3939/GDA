#pragma once
#include "Messenger.h"
#include <vector>


class GoalBase;
class ActionBase;
class Director;


class Manager :
    public Messenger
{
public:
    Manager(Messenger* pNext,GoalBase* pDefaultGoal = nullptr);
    virtual ~Manager() = 0;

    virtual void Update(float fDeltaTime);

    GoalBase* GetGoal();

    void SetGoal(GoalBase* pGoal);

    void GetNewPlan();


    std::vector<ActionBase*>& GetAvailableAction();
    std::vector<ActionBase*>& GetCurrentPlan();

    std::map<std::string, bool>& GetExpectedWS();
private:
    GoalBase* m_pGoal;
    Director* m_pDirector;

    //Lists for getting a plan
    std::vector<ActionBase*> m_apAvailableActions;
    std::vector<ActionBase*> m_apCurrentPlan;
    std::vector<GoalBase*> m_apAvailableGoals;
    std::map<std::string, bool> m_apExpectedWS;

    //ew sorry
    //Caching whats needed to send a message to get a plan
    Message<Manager*>* m_pPlanMessage;

    //A list of who any message is sent to
    std::vector<unsigned int> m_anMessageToID;
};

