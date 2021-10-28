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
    virtual ~Manager();


    //-------------------
    // Setup functions
    // for  2 reasons:
    // 1. Need pure virtuals
    // 2.  So that theres a place
    // for user to actually write the code
    // to create the goals / actions
    //-------------------
    virtual void SetUpActions() = 0;
    virtual void SetUpGoals() = 0;

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


    void ConsiderNewGoal();

    //-------------------
    // Get lists
    //-------------------
    ActionList& GetAvailableActions();
    ActionList& GetCurrentPlan();
    GoalList& GetAvailableGoals();
    WorldStateMap& GetCurrentWS();

    WorldStateMap& GetCurrentWSList();
   
    Expectations& GetExpectations();
    std::vector<std::string>& GetExplanations();
    

    Observer* GetObserver();

    void SetMitigation(Goal* pGoal);

    Goal* GetMitigation();

	
private:
    //Current goal of this manager
    Goal* m_pGoal;
    Goal* m_pMitigation;

    GoalList m_apAvailableGoals;

    //Components of Manager
    Director* m_pDirector;
    Observer* m_pObserver;

    //Lists for getting a plan
    ActionList m_apAvailableActions;
    ActionList m_apCurrentPlan;

    ActionList m_apMitigationPlan;

    //the action this manager is currently performing
    unsigned int m_nCurrentAction;

    //Cache map for world state
    WorldStateMap m_aCurrentWS;
    
    //Caching whats needed to send a message to get a plan
    Message* m_pPlanMessage;


    Message* m_pMitigationMessage;
    

    Message* m_pCurrentWS;

    bool m_bNewGoal;

    //A list of who any message is sent to
    std::vector<unsigned int> m_anMessageToID;
};

