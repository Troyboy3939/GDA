#pragma once
#include "Manager.h"
#include "Message.h"
#include "ResourceClass.h"
class AIComponent;
class Empire;
class Villager;
class Building;

class EcoManager :
    public Manager
{
public:

    enum class ActionID
    {
        CreateVillager,
        CreateFoodStorage,
        CreateWoodStorage,
        CreateGoldStorage,
        GetFood,
        GetWood,
        GetGold,
        AgeUp
    };



    EcoManager(Blackboard* pBlackboard, AIComponent* pAI,Goal* pDefaultGoal = nullptr);
    ~EcoManager();


    void SetUpExpectations();
    void SetUpGoals() override;
    void SetUpActions() override;

    void Update(float fDeltaTime) override;


    void GetNewPlan() override;
protected:
    void AddCutter(Villager* pVill);
    void AddMiner(Villager* pVill);
    void AddGatherer(Villager* pVill);


    void UpdateWorldStates();


    void CreateVillager(float fDeltaTime);
    void CreateStorage(Resource::Type eType, float fDeltaTime);
    void AgeUp(float fDeltaTime);
    void GetFood(float fDeltaTime);
    void GetWood(float fDeltaTime);
    void GetGold(float fDeltaTime);

    void NextAction();



    void HandleMessage(Message* pMessage) override;


    int m_nVillagerCount;
    int m_nUnitCount;




    //Keep track of how many villagers are at each resource
    std::vector<Villager*> m_apCutters;
    std::vector<Villager*> m_apMiners;
    std::vector<Villager*> m_apGatherers;
    std::vector<Villager*> m_apIdle;
    std::vector<Villager*> m_apUnits;


    std::vector<Expectation*> m_Expectations;


    Building* m_pBuilding;
    AIComponent* m_pAI;
    Empire* m_pTeam;

    bool m_bWaiting;


    float m_fTimer;

};

