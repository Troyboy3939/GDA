#pragma once
#include "Messenger.h"
#include "Message.h"
#include <vector>
#include <map>
#include <string>


class Goal;
class Action;
class Director;
class Observer;

class Manager :
    public Messenger
{
public:
    //-------------------
    // Constructor / Destructor
    //-------------------
    Manager(Blackboard* pBlackboard,Goal* pDefaultGoal = nullptr);
    virtual ~Manager() = 0;

    //-------------------
    // Called every frame
    //-------------------
    virtual void Update(float fDeltaTime);

    //-------------------
    // returns the goal currently being pursed
    //-------------------
    Goal* GetGoal();

    //-------------------
    // Changes the goal being pursued
    //-------------------
    void SetGoal(Goal* pGoal);

    //-------------------
    // Tells Manager to update its current plan
    //-------------------
    void GetNewPlan();

    //-------------------
    // Get lists
    //-------------------
    std::vector<Action*>& GetAvailableAction();
    std::vector<Action*>& GetCurrentPlan();
    std::map<std::string, bool>& GetExpectedWS();
    std::vector<Goal*>& GetAvailableGoals();
    std::map<std::string, bool>& GetCurrentWS();

    std::map<std::string, bool>& GetCurrentWSList();
   
private:
    Goal* m_pGoal;
    Director* m_pDirector;
    Observer* m_pObserver;

    //Lists for getting a plan
    std::vector<Action*> m_apAvailableActions;
    std::vector<Action*> m_apCurrentPlan;
    std::vector<Goal*> m_apAvailableGoals;
    


    //expected world state after plan is completed
    std::map<std::string, bool> m_apExpectedWS;

    std::map<std::string, bool> m_aCurrentWS;
    
    //Caching whats needed to send a message to get a plan
    Message* m_pPlanMessage;
    

    Message* m_pCurrentWS;
    

    //A list of who any message is sent to
    std::vector<unsigned int> m_anMessageToID;
};

