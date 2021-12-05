#include "EcoManager.h"
#include <functional>
#include "Expectation.h"
#include "AIComponent.h"
#include "Empire.h"
#include "Villager.h"
#include "Observer.h"
#include "Blackboard.h"
#include "TownCentre.h"
#include "Building.h"
EcoManager::EcoManager(Blackboard* pBlackboard, AIComponent* pAI, Goal* pDefaultGoal) : Manager(pBlackboard, pDefaultGoal)
{
	SetUpExpectations();
	SetUpActions();
	SetUpGoals();

	m_fTimer = 0.0f;

	m_pAI = pAI;
	
	if (m_pAI)
	{
		m_pTeam = m_pAI->GetTeam();

		auto& rapUnits = m_pTeam->GetUnits();

		//add initial units into the idle vector
		for (auto pUnit : rapUnits)
		{
			m_apIdle.push_back(static_cast<Villager*>(pUnit));

			m_apUnits.push_back(static_cast<Villager*>(pUnit));
		}
	}


	m_nVillagerCount = 3;
	//first one added is get to second age
	m_pGoal = m_apAvailableGoals[0];




	m_nCurrentAction = 0;

	m_bWaiting = false;

	m_nUnitCount = 3;
}

EcoManager::~EcoManager()
{
}


void EcoManager::SetUpExpectations()
{

}

void EcoManager::SetUpGoals()
{
	//-------------------------------------------------------------------------------------------------
	// 	Age up to 2
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnGetToSecIsValid = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre);
	};
	std::string sSecondA = "SecondAge";

	auto pGetToSecondAge = new Goal(sSecondA, fnGetToSecIsValid, {});




	std::function<bool(Manager* pMan)> fnGetFood = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre);
	};


	std::string sGetFood = "GettingFood";

	auto pGetFood = new Goal(sGetFood, fnGetFood, {});


	std::function<bool(Manager* pMan)> fnGetWood = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre);
	};


	std::string sGetWood = "GettingWood";

	auto pGetWood = new Goal(sGetWood, fnGetWood, {});


	std::function<bool(Manager* pMan)> fnGetGold = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre);
	};


	std::string sGetGold = "GettingGold";

	auto pGetGold = new Goal(sGetGold, fnGetGold, {});



	m_apAvailableGoals.push_back(pGetFood);
	m_apAvailableGoals.push_back(pGetWood);
	m_apAvailableGoals.push_back(pGetGold);

}

void EcoManager::SetUpActions()
{
	
	//-------------------------------------------------------------------------------------------------
	// 	Age up to 2
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnAgeUpIsValid = [=](Manager* pMan) -> bool
	{
		return m_pTeam->GetAge() == 1;
	};

	auto pAgeUp2 = new Action(800.0f, fnAgeUpIsValid, "SecondAge", {"GettingGold","GettingFood", "GettingWood"});

	m_apAvailableActions.push_back(pAgeUp2);

	pAgeUp2->SetID(static_cast<int>(ActionID::AgeUp));

	
	//-------------------------------------------------------------------------------------------------
	//  Get More Wood
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnGetWoodIsValid = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre) || m_apMiners.size() >= 6 * m_pTeam->GetAge() || m_apGatherers.size() >= 6 * m_pTeam->GetAge() || !m_apIdle.empty();
	};


	auto pGetWood = new Action(51.0f, fnGetWoodIsValid, "GettingWood", { "HasSpareVillager", "StorageNearWood"});

	pGetWood->SetID(static_cast<int>(ActionID::GetWood));

	//-------------------------------------------------------------------------------------------------
	//  Get More Food
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnGetFoodIsValid = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre) || m_nVillagerCount > 0;
	};


	auto pGetFood = new Action(53.0f, fnGetFoodIsValid, "GettingFood", { "HasSpareVillager", "StorageNearFood" });
	pGetFood->SetID(static_cast<int>(ActionID::GetFood));


	//-------------------------------------------------------------------------------------------------
	//  Get More Gold
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnGetGoldIsValid = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre) || m_apMiners.size() >= 6 * m_pTeam->GetAge() || m_apCutters.size() >= 6 * m_pTeam->GetAge() || !m_apIdle.empty();
	};


	auto pGetGold = new Action(50.0f, fnGetGoldIsValid, "GettingGold", { "HasSpareVillager" , "StorageNearGold"});
	pGetGold->SetID(static_cast<int>(ActionID::GetGold));


	m_apAvailableActions.push_back(pGetWood);
	m_apAvailableActions.push_back(pGetGold);
	m_apAvailableActions.push_back(pGetFood);
	//-------------------------------------------------------------------------------------------------
	//  Create Villager
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnCreateVillager = [=](Manager* pMan) -> bool
	{
		return m_pTeam->HasBuilding(Building::BType::TownCentre);
	};


	auto pCreateVillager = new Action(50.0f, fnCreateVillager, "HasSpareVillager", {"HasTownCenter"});
	m_apAvailableActions.push_back(pCreateVillager);
	pCreateVillager->SetID(static_cast<int>(ActionID::CreateVillager));

	//-------------------------------------------------------------------------------------------------
	//  Create Storage near food
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnCreateFStorage = [=](Manager* pMan) -> bool
	{

		//if you have at least 1 villager you can do this
		return m_nVillagerCount > 0;
	};


	auto pCreateFoodStorage = new Action(100.0f, fnCreateFStorage,"StorageNearFood", {});
	m_apAvailableActions.push_back(pCreateFoodStorage);
	pCreateFoodStorage->SetID(static_cast<int>(ActionID::CreateFoodStorage));



	//-------------------------------------------------------------------------------------------------
	//  Create Storage near Gold
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnCreateGStorage = [=](Manager* pMan) -> bool
	{

		//if you have at least 1 villager you can do this
		return m_nVillagerCount > 0;
	};


	auto pCreateGoldStorage = new Action(100.0f, fnCreateGStorage, "StorageNearGold", {});
	m_apAvailableActions.push_back(pCreateGoldStorage);
	pCreateGoldStorage->SetID(static_cast<int>(ActionID::CreateGoldStorage));




	//-------------------------------------------------------------------------------------------------
	//  Create Storage near Wood
	//-------------------------------------------------------------------------------------------------

	std::function<bool(Manager* pMan)> fnCreateWStorage = [=](Manager* pMan) -> bool
	{

		//if you have at least 1 villager you can do this
		return m_nVillagerCount > 0;
	};


	auto pCreateWoodStorage = new Action(100.0f, fnCreateWStorage, "StorageNearWood", {});
	m_apAvailableActions.push_back(pCreateWoodStorage);
	pCreateWoodStorage->SetID(static_cast<int>(ActionID::CreateWoodStorage));




}

void EcoManager::Update(float fDeltaTime)
{
	Manager::Update(fDeltaTime);


	UpdateWorldStates();

	m_fTimer += fDeltaTime;

	if (m_fTimer > 5.0f || m_apCurrentPlan.empty())
	{
		m_fTimer = 0.0f;


		if (m_pBlackboard->GetWorldStateValue("GettingFood"))
		{
			m_pGoal = m_apAvailableGoals[1];
		}

		if (m_pBlackboard->GetWorldStateValue("GettingWood"))
		{
			m_pGoal = m_apAvailableGoals[m_apAvailableGoals.size() - 1];
		}


		GetNewPlan();
	}

	//update villager lists
	if (!m_apCurrentPlan.empty())
	{
		if (m_nCurrentAction >= 0 && m_nCurrentAction < m_apCurrentPlan.size())
		{
			auto pAction = m_apCurrentPlan[m_nCurrentAction];

			if (pAction)
			{
				switch (static_cast<ActionID>(pAction->GetID()))
				{
				case EcoManager::ActionID::CreateVillager:
				{
					CreateVillager(fDeltaTime);
				}
					break;
				case EcoManager::ActionID::CreateFoodStorage:
				{
					CreateStorage(Resource::Type::FOOD,fDeltaTime);
				}
				break;
				case EcoManager::ActionID::CreateWoodStorage:
				{
					CreateStorage(Resource::Type::WOOD, fDeltaTime);
				}
				break;
				case EcoManager::ActionID::CreateGoldStorage:
				{
					CreateStorage(Resource::Type::GOLD, fDeltaTime);
				}
				break;
				case EcoManager::ActionID::GetFood:
				{
					GetFood(fDeltaTime);
				}
					break;
				case EcoManager::ActionID::GetWood:
				{
					GetWood(fDeltaTime);
				}
					break;
				case EcoManager::ActionID::GetGold:
				{
					GetGold(fDeltaTime);
				}
					break;
				case EcoManager::ActionID::AgeUp:
				{
					AgeUp(fDeltaTime);
				}
					break;
				default:
					break;
				}
			}
		}
	}
	else
	{
		GetNewPlan();
	}

	auto nCutters = m_apCutters.size();
	auto nMiners = m_apMiners.size();
	auto nGatho = m_apGatherers.size();

	//if even after doing all of this if there are still idle villagers, then
	if (!m_apIdle.empty())
	{



		std::vector<Villager*>* papSmallestNonZero = nullptr;
		if (nGatho > 0)
		{
			papSmallestNonZero = &m_apGatherers;
		}
		if ( nGatho < nCutters)
		{
			papSmallestNonZero = &m_apGatherers;
		}
		else if(nCutters > 0)
		{
			papSmallestNonZero = &m_apCutters;
		}

		if (papSmallestNonZero)
		{
			if (nMiners > 0 && nMiners < papSmallestNonZero->size())
			{
				papSmallestNonZero = &m_apMiners;
			}


			for (auto pVill : m_apIdle)
			{
				pVill->StartCollectingResource((*papSmallestNonZero)[0]->GetResource());
				papSmallestNonZero->push_back(pVill);
			}

			m_apIdle.clear();
		}
	}


	

	auto& rapUnits = m_pTeam->GetUnits();


	if (rapUnits.size() > m_apUnits.size())
	{
		for (auto pVill : rapUnits)
		{
			if (std::find(m_apUnits.begin(), m_apUnits.end(), pVill) != m_apUnits.end())
			{
				continue;
			}
			else
			{
				m_apUnits.push_back(static_cast<Villager*>(pVill));
				m_apIdle.push_back(static_cast<Villager*>(pVill));
			}
		}
	}

	for (auto pVill : m_apGatherers)
	{
		if (pVill && !pVill->GetResource() && !pVill->GetBuilding())
		{
			for (auto pVill2 : m_apGatherers)
			{
				if (pVill2 && pVill != pVill2)
				{
					if (pVill2->GetResource())
					{
						pVill->StartCollectingResource(pVill2->GetResource());
						return;
					}

					if (pVill2->GetBuilding())
					{
						pVill->HelpBuild(Building::BType::Storage, pVill2->GetBuilding()->GetPosition());
					}
				}
			}
		}
	}

	for (auto pVill : m_apCutters)
	{
		if (pVill && !pVill->GetResource() && !pVill->GetBuilding())
		{
			for (auto pVill2 : m_apCutters)
			{
				if (pVill2 && pVill != pVill2)
				{
					if (pVill2->GetResource())
					{
						pVill->StartCollectingResource(pVill2->GetResource());
						return;
					}

					if (pVill2->GetBuilding())
					{
						pVill->HelpBuild(Building::BType::Storage, pVill2->GetBuilding()->GetPosition());
					}
				}
			}
		}
	}

	for (auto pVill : m_apMiners)
	{
		if (pVill && !pVill->GetResource() && !pVill->GetBuilding())
		{
			for (auto pVill2 : m_apMiners)
			{
				if (pVill2 && pVill != pVill2)
				{
					if (pVill2->GetResource())
					{
						pVill->StartCollectingResource(pVill2->GetResource());
						return;
					}

					if (pVill2->GetBuilding())
					{
						pVill->HelpBuild(Building::BType::Storage, pVill2->GetBuilding()->GetPosition());
					}
				}
			}
		}
	}

}

void EcoManager::GetNewPlan()
{
	Manager::GetNewPlan();

	m_bWaiting = false;
}

void EcoManager::AddCutter(Villager* pVill)
{
	m_apCutters.push_back(pVill);

	if (m_apCutters.size() >= m_apUnits.size() && (!m_apGatherers.empty() || !m_apMiners.empty()))
	{
		auto x = 0;
	}
}

void EcoManager::AddMiner(Villager* pVill)
{
	m_apMiners.push_back(pVill);

	if (m_apMiners.size() >= m_apUnits.size() && (!m_apGatherers.empty() || !m_apCutters.empty()))
	{
		auto x = 0;
	}
}

void EcoManager::AddGatherer(Villager* pVill)
{
	m_apGatherers.push_back(pVill);

	if (m_apGatherers.size() >= m_apUnits.size() && (!m_apMiners.empty() || !m_apCutters.empty()))
	{
		auto x = 0;
	}
}

void EcoManager::UpdateWorldStates()
{

	auto pTC = m_pTeam->GetTownCentre();

	if (pTC)
	{
		m_pBlackboard->UpdateWorldState("HasTownCenter",true);



		auto pWood = m_pTeam->FindNearbyResource(pTC->GetPosition(),Resource::Type::WOOD);
		auto pFood = m_pTeam->FindNearbyResource(pTC->GetPosition(),Resource::Type::FOOD);
		auto pGold = m_pTeam->FindNearbyResource(pTC->GetPosition(),Resource::Type::GOLD);


		if (pWood)
		{
			auto v2WoodPos = pWood->GetPosition();


			auto pWoodStorage = m_pTeam->FindClosestStorage(v2WoodPos);

			auto v2WsPos = pWoodStorage->GetPosition();

			auto v2Dis = v2WoodPos - v2WsPos;

			auto bValue = false;
			//if there is one within 5 blocks
			if (v2Dis.magnitudeSq() < 320 * 320)
			{
				bValue = true;
			}


			m_pBlackboard->UpdateWorldState("StorageNearWood", bValue);
		}

		if (pFood)
		{
			auto v2FoodPos = pFood->GetPosition();


			auto pFoodStorage = m_pTeam->FindClosestStorage(v2FoodPos);

			auto v2WsPos = pFoodStorage->GetPosition();

			auto v2Dis = v2FoodPos - v2WsPos;

			auto bValue = false;
			//if there is one within 5 blocks
			if (v2Dis.magnitudeSq() < 320 * 320)
			{
				bValue = true;
			}


			m_pBlackboard->UpdateWorldState("StorageNearFood", bValue);
		}

		if (pGold)
		{
			auto v2GoldPos = pGold->GetPosition();


			auto pGoldStorage = m_pTeam->FindClosestStorage(v2GoldPos);

			auto v2WsPos = pGoldStorage->GetPosition();

			auto v2Dis = v2GoldPos - v2WsPos;

			auto bValue = false;
			//if there is one within 5 blocks
			if (v2Dis.magnitudeSq() < 320 * 320)
			{
				bValue = true;
			}


			m_pBlackboard->UpdateWorldState("StorageNearGold", bValue);
		}
	}


	auto nAmount = 6 * m_pTeam->GetAge();

	if(m_apGatherers.size() >= 6)
	{
		m_pBlackboard->UpdateWorldState("GettingFood", true);
	}

	if (m_apCutters.size() >= 6)
	{
		m_pBlackboard->UpdateWorldState("GettingWood", true);
	}

	if (m_apMiners.size() >= 6)
	{
		m_pBlackboard->UpdateWorldState("GettingGold", true);
	}



	if (!m_apIdle.empty())
	{
		m_pBlackboard->UpdateWorldState("HasSpareVillager", true);
	}
	else if (m_apCutters.size() > nAmount || m_apGatherers.size() > nAmount || m_apMiners.size() > nAmount)
	{

		m_pBlackboard->UpdateWorldState("HasSpareVillager", true);
	}
	else
	{
		m_pBlackboard->UpdateWorldState("HasSpareVillager", false);
	}
}

void EcoManager::CreateVillager(float fDeltaTime)
{

	auto pTC = m_pTeam->GetTownCentre();

	if (pTC)
	{
		if (!m_bWaiting)
		{

			if (m_pTeam->GetFood() >= 50.0f)
			{
				m_pTeam->SpendResources(Vector3(0.0f,50.0f,0.0f));

				pTC->AddActionToQueue(Icon::IType::Villager);
				m_bWaiting = true;

				m_nUnitCount = m_pTeam->GetUnitCount();

				return;
			}
			else if (!m_apIdle.empty())
			{
				NextAction();
			}
			
		}
		else
		{
			
			auto& rapUnits = m_pTeam->GetUnits();

			if (rapUnits.size() > m_apUnits.size())
			{
				for (auto pUnit : rapUnits)
				{
					auto pVill = static_cast<Villager*>(pUnit);

					if (std::find(m_apUnits.begin(), m_apUnits.end(), pVill) != m_apUnits.end())
					{
						continue;
					}


					if (pVill->GetState() == Villager::State::Idle)
					{
						m_apIdle.push_back(pVill);
						m_apUnits.push_back(pVill);
						m_nVillagerCount++;
					}
				}

				NextAction();
			}


		}
	}

	
	

}


void EcoManager::CreateStorage(Resource::Type eType, float fDeltaTime)
{
	if (!m_bWaiting)
	{




		if (m_apCurrentPlan.size() >= 2)
		{
			m_pBuilding = nullptr;

			Resource* pResource = nullptr;

			Villager* pVill = nullptr;

			if (!m_apIdle.empty())
			{
				pVill = m_apIdle[0];
			}
			else
			{
				auto nAmount = m_pTeam->GetAge() * 6;

				if (m_apCutters.size() > nAmount && eType != Resource::Type::WOOD)
				{
					pVill = m_apCutters[0];
				}
				else if (m_apGatherers.size() > nAmount && eType != Resource::Type::FOOD)
				{
					pVill = m_apGatherers[0];
				}
				else if (m_apMiners.size() > nAmount && eType != Resource::Type::GOLD)
				{
					pVill = m_apMiners[0];
				}
				else
				{
					//GetNewPlan();
					return;
				}
			}


			auto bBreak = false;
	
			pResource = m_pTeam->FindNearbyResource(pVill->GetPosition(), eType);

			


			//if both aren't not nullptr
			if (pResource && pVill)
			{
				auto pFloor = m_pTeam->GetFloor();

				auto v2ToResource =  pVill->GetPosition() - pResource->GetPosition();

				v2ToResource.normalise();

				auto v2Location = pResource->GetPosition();


				if (eType == Resource::Type::WOOD)
				{
					auto v2Location = pResource->GetPosition();

				}

				while (true)
				{
					//Move in the direction of the unit
					v2Location += (v2ToResource * 64);


					if (pFloor->CanBuildAt(v2Location))
					{
						if (!m_apIdle.empty())
						{
							for (auto pUnit : m_apIdle)
							{

								if (!m_pBuilding)
								{
									if (m_pTeam->GetWood() >= 100.0f)
									{
										auto bExists = false;

										switch (eType)
										{
										case Resource::Type::WOOD:
										{
											if (m_pBlackboard->GetWorldStateValue("StorageNearbyWood"))
											{
												NextAction();
												bExists = true;
											}
										}
										break;
										case Resource::Type::GOLD:
											if (m_pBlackboard->GetWorldStateValue("StorageNearbyGold"))
											{
												NextAction();
												bExists = true;
											}
											break;
										case Resource::Type::FOOD:
											if (m_pBlackboard->GetWorldStateValue("StorageNearbyGold"))
											{
												NextAction();
												bExists = true;
											}
											break;
										default:
											break;
										}
										if (!bExists)
										{
											m_pBuilding = pUnit->CreateBuilding(Building::BType::Storage, v2Location);
										}
									}
								}
								else
								{
									pUnit->HelpBuild(Building::BType::Storage, v2Location);
								}



								m_bWaiting = true;
								switch (pResource->GetType())
								{
									case Resource::Type::FOOD:
									{
										if (pUnit)
										{
											AddGatherer(pUnit);
											break;
										}
									}
									case Resource::Type::WOOD:
									{
										if (pUnit)
										{
											AddCutter(pUnit);
										}
									}
									break;
									case Resource::Type::GOLD:
									{
										if (pUnit)
										{
											AddMiner(pUnit);
										}
									}
									break;
								}
							}
						}
						m_apIdle.clear();

						return;
					}
				}
			}

		}

	}
	else
	{
		if (m_pBuilding)
		{
			if (m_pBuilding->GetPercentageComplete() >= 100.0f)
			{
				NextAction();
			}
		}
	}
}
	


void EcoManager::AgeUp(float fDeltaTime)
{
	auto pTC = m_pTeam->GetTownCentre();

	if (pTC)
	{
		if (!m_bWaiting)
		{
			pTC->AddActionToQueue(Icon::IType::Villager);
			m_bWaiting = true;

			m_nUnitCount = m_pTeam->GetUnitCount();
		}
		else
		{
			if (m_nUnitCount < m_pTeam->GetUnitCount())
			{
				m_nVillagerCount++;

				m_apIdle.push_back(dynamic_cast<Villager*>(m_pTeam->GetLatestUnit(Unit::UType::Villager)));

				m_apUnits.push_back(m_apIdle[m_apIdle.size() - 1]);


				NextAction();
			}


		}
	}







}

void EcoManager::GetFood(float fDeltaTime)
{
	if (!m_apIdle.empty())
	{
		for (auto pVill : m_apIdle)
		{
			if (pVill)
			{
				
				pVill->StartCollectingResource(m_pTeam->FindNearbyResource(pVill->GetPosition(), Resource::Type::FOOD));
				
				AddGatherer(pVill);
			}
		}

		m_apIdle.clear();
	}
	


	if(m_apGatherers.size() >= m_pTeam->GetAge() * 6)
	{
		NextAction();
	}
}

void EcoManager::GetWood(float fDeltaTime)
{
	if (!m_apIdle.empty())
	{
		for (auto pVill : m_apIdle)
		{
			if (pVill)
			{

				pVill->StartCollectingResource(m_pTeam->FindNearbyResource(pVill->GetPosition(), Resource::Type::WOOD));

				AddCutter(pVill);
			}
		}

		m_apIdle.clear();
	}

	if (m_apCutters.size() >= m_pTeam->GetAge() * 6)
	{
		NextAction();
	}
}

void EcoManager::GetGold(float fDeltaTime)
{
	if (!m_apIdle.empty())
	{
		for (auto pVill : m_apIdle)
		{
			if (pVill)
			{

				pVill->StartCollectingResource(m_pTeam->FindNearbyResource(pVill->GetPosition(), Resource::Type::GOLD));
			}
		}
	}
	

	NextAction();

}

void EcoManager::NextAction()
{
	m_nCurrentAction++;

	m_bWaiting = false;
}

void EcoManager::HandleMessage(Message* pMessage)
{
	
}
