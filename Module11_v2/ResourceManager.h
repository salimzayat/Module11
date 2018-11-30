#pragma once

#include <map>
#include <list>
#include "Defines.h"


class ResourceManager
{
public:
	static ResourceManager* GetInst()
	{
		if (s_pInst == nullptr)
		{
			s_pInst = new ResourceManager();
		}
		return s_pInst;
	}

	std::list<int> GetPlayerIdsForTeam(int teamId);
	const TeamConfig& GetTeam(int teamId);
	const PlayerConfig& GetPlayer(int playerId);
	int GetTeamCount();
	void LoadXml();

private:
	ResourceManager();
	~ResourceManager();



	std::list<PlayerConfig> m_playerConfigs;
	std::list<TeamConfig> m_teamConfigs;
	std::map<int, int> m_playerToTeamMapping;
	bool m_isLoaded;

	static ResourceManager* s_pInst;

};

