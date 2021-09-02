#pragma once
#include "Messenger.h"
#include "Message.h"
#include <vector>
#include <map>
#include <string>


class GoalBase;
class ActionBase;
class Director;
class Observer;

class Manager :
    public Messenger
{
public:
    //-------------------
    // Constructor / Destructor
    //-------------------
    Manager(Messenger* pNext,GoalBase* pDefaultGoal = nullptr);
    virtual ~Manager() = 0;

    //-------------------
    // 
    //-------------------
    virtual void Update(float fDeltaTime);

    GoalBase* GetGoal();

    void SetGoal(GoalBase* pGoal);

    void GetNewPlan();

    //-------------------
    // Get lists
    //-------------------
    std::vector<ActionBase*>& GetAvailableAction();
    std::vector<ActionBase*>& GetCurrentPlan();
    std::map<std::string, bool>& GetExpectedWS();
    std::vector<GoalBase*>& GetAvailableGoals();
    std::map<std::string, bool>& GetCurrentWS();
private:
    GoalBase* m_pGoal;
    Director* m_pDirector;
    Observer* m_pObserver;

    //Lists for getting a plan
    std::vector<ActionBase*> m_apAvailableActions;
    std::vector<ActionBase*> m_apCurrentPlan;
    std::vector<GoalBase*> m_apAvailableGoals;

    //expected world state after plan is completed
    std::map<std::string, bool> m_apExpectedWS;

    
    //Caching whats needed to send a message to get a plan
    Message<Manager*>* m_pPlanMessage;
    

    //A list of who any message is sent to
    std::vector<unsigned int> m_anMessageToID;
};

