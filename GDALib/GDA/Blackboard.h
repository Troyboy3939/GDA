#pragma once
#include "Messenger.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "PlansOverseer.h"


class BlackboardData;
class Manager;
class Goal;
class Expectation;

using Response = std::pair<Manager*, Goal*>;

class Blackboard :
    public Messenger
{
public:



    template<typename T>
    using StringMap = std::unordered_map<std::string, T>;
    Blackboard(PlansOverseer* pOverseer);
    ~Blackboard();

    //----------------------
    // Update function, called every frame
    //----------------------
    void Update(float fDeltaTime);

    
    //---------------------
    // return true if message is being handled, is called when a message is being sent to this messenger
    //---------------------
    bool SendMessage(Message* pMessage);

    //----------------------
    // Adds a manager to this blackboard
    //----------------------
    void AddManager(Manager* pManager);

    //----------------------
    // Returns any shared data with the key
    //----------------------
    BlackboardData* GetValue(std::string& rsKey);

    void AddResponse(std::string& rsExplanation, Response response);

    Goal* GetResponse(std::string& rsExplanation, Manager* pManager);

private:

    //----------------------
    // turns rsKey into a substring from
    // the first space in rsString
    //----------------------
    void GetSubString(const std::string& rsString, std::string& rsKey);

    //----------------------
    // This is called when this is sent a message that is intended for this blackboard
    //----------------------
    void HandleMessage(Message* pMessage) override;



    void GoalFormulator(Manager* pManager);

    //What the managers think the current world state is
    StringMap<bool> m_aWorldState;

    //Map keys to specific data that is given to by the managers
	StringMap<BlackboardData*> m_apData;

    //List of managers that this blackboard with communicate with
    std::vector<Manager*> m_apManagers;

    std::unordered_multimap<std::string, Response> m_Reponses;

    //pointer to the plans overseeer
    PlansOverseer* m_pPlansOverseer;


    


};

