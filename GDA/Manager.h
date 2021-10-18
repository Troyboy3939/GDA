#pragma once
#include "Messenger.h"
#include "Message.h"
#include <vector>
#include <map>
#include <string>

#include "Goal.h"

class Action;
class Director;
class Observer;

//Alias Declaration. Far easier to read
using WorldStateMap = std::unordered_map<std::string, bool>;
using WorldStateList = std::vector<std::string>;


using ActionList = std::vector<Action*>;
using GoalList = std::vector<Goal*>;



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
    // Returns index of action being performed
    //-------------------
    unsigned int GetCurrentAction();


    void MessageBlackboard(Message* pMessage);

    //-------------------
    // Get lists
    //-------------------
    ActionList& GetAvailableActions();
    ActionList& GetCurrentPlan();
    GoalList& GetAvailableGoals();
    WorldStateMap& GetCurrentWS();

    WorldStateMap& GetCurrentWSList();
   
    Expectations& GetExpectations();
private:
    //Current goal of this manager
    Goal* m_pGoal;


    //Components of Manager
    Director* m_pDirector;
    Observer* m_pObserver;

    //Lists for getting a plan
    ActionList m_apAvailableActions;
    ActionList m_apCurrentPlan;
    GoalList m_apAvailableGoals;

    //the action this manager is currently performing
    unsigned int m_nCurrentAction;

    WorldStateMap m_aCurrentWS;
    
    //Caching whats needed to send a message to get a plan
    Message* m_pPlanMessage;
    

    Message* m_pCurrentWS;
    

    //A list of who any message is sent to
    std::vector<unsigned int> m_anMessageToID;
};

