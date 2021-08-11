#pragma once

class Manager;


class Director
{
public:
	Director(Manager* pManager);

	void PickGoal();
private:
	Manager* m_pManager;

};

