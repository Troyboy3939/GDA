#pragma once
#include "Messenger.h"
#include <unordered_map>
#include <string>
#include <vector>

class BlackboardData;
class Manager;
class PlansOverseer;


class Blackboard :
    public Messenger
{
public:
    Blackboard(PlansOverseer* pOverseer);

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


private:

    //----------------------
    // This is called when this is sent a message that is intended for this blackboard
    //----------------------
    void HandleMessage(Message* pMessage);

    //What the managers think the current world state is
    std::unordered_map<std::string, bool> m_aWorldState;

    //Map keys to specific data that is given to by the managers
    std::unordered_map<std::string, BlackboardData*> m_apData;

    //List of managers that this blackboard with communicate with
    std::vector<Manager*> m_apManagers;

    //pointer to the plans overseeer
    PlansOverseer* m_pPlansOverseer;


    


};

