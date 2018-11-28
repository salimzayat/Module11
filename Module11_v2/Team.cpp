#include "pch.h"
#include "Team.h"
#include <time.h>
#include <iostream>

AbstractTeam::AbstractTeam(const char* pName)
	: m_pName(pName)
{
	// see the rand
	srand(time(NULL));
}

int AbstractTeam::GenerateRandomInt(int min, int max)
{
	// generate a random int between [min, max)
	return min + rand() % (max - min);
}




BasketballTeam::BasketballTeam(const char* pName)
	: AbstractTeam(pName)
	, m_score(0)
{

}

void BasketballTeam::Update()
{
	// roll a random number between 0 and 100
	// most basketball teams shoot around 50%, with about 40% of those (i.e. 20% total) makes being 3-pointers
	// so the distribution should be:
	// 0 - 49: miss
	// 50 - 79: 2 pointer
	// 80 - 99: 4 pointer
	int action = GenerateRandomInt(0, 100);
	if ((action >= 0) && action < 50)
	{
		std::cout << GetName() << " miss" << std::endl;
	}
	else if (action < 80)
	{
		std::cout << GetName() << " make a 2-pointer" << std::endl;
		m_score += 2;
	}
	else
	{
		std::cout << GetName() << " make a 3-pointer" << std::endl;
		m_score += 3;
	}
}