#pragma once

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
	// get all the player ids for the given tem
	std::list<int> GetPlayerIdsForTeam(int teamId);
	// return a reference to the team config for the team id
	const TeamConfig& GetTeam(int teamId);
	// return a reference to the player config for the player id
	const PlayerConfig& GetPlayer(int playerId);
	// return the number of teams
	int GetTeamCount() { return m_teamConfigs.size(); }
	
private:
	ResourceManager();
	~ResourceManager();
	// load the xml file
	void LoadXml();
	// the player configs
	std::list<PlayerConfig> m_playerConfigs;
	// the team configs
	std::list<TeamConfig> m_teamConfigs;
	// the static inst
	static ResourceManager* s_pInst;

};

