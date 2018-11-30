#include "pch.h"
#include "ResourceManager.h"
#include <string>
#include "tinyxml2.h"
using namespace tinyxml2;

ResourceManager* ResourceManager::s_pInst = nullptr;

ResourceManager::ResourceManager()
{
	// we need to load in the XML file for this data
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::LoadXml()
{
	// we have a path we want to load
	XMLDocument doc;
	XMLError err = doc.LoadFile("demo.xml");
	XMLElement* root = doc.FirstChildElement("config");
	// get the teams first
	XMLNode* teamsNode = root->FirstChildElement("teams");

	for (XMLElement* teamElem = teamsNode->FirstChildElement("team"); teamElem != NULL; teamElem = teamElem->NextSiblingElement())
	{
		int id = -1;
		const char* name = "foo";
		const char* city = "foo";
		const char* shortName = "ff";
		
		teamElem->QueryAttribute("id", &id);
		teamElem->QueryStringAttribute("name", &name);
		teamElem->QueryStringAttribute("city", &city);
		teamElem->QueryStringAttribute("short_name", &shortName);

		std::string name2 = std::string(name);
		m_teamConfigs.push_back({ id, name, city, shortName });
	}
	// now grab the players
	// get the teams first
 	XMLNode* playersNode = root->FirstChildElement("players");

	for (XMLElement* playerElem = playersNode->FirstChildElement("player"); playerElem != NULL; playerElem = playerElem->NextSiblingElement())
	{
		int id = -1;
		const char* team = "ff";
		const char* name = "foo";
		int off2Point = 0;
		int off3Point = 0;
		int def = 0;
		const char* position = "";

		playerElem->QueryAttribute("id", &id);
		playerElem->QueryStringAttribute("name", &name);
		playerElem->QueryStringAttribute("team", &team);
		playerElem->QueryStringAttribute("position", &position);
		// now, we grab the offense and defense from the appropriate tags
		XMLNode* offenseNode = playerElem->FirstChildElement("offense");
		offenseNode->FirstChildElement("two_point")->QueryIntText(&off2Point);
		offenseNode->FirstChildElement("three_point")->QueryIntText(&off3Point);
		playerElem->FirstChildElement("defense")->QueryIntText(&def);

		m_playerConfigs.push_back({ id, name, team, off2Point, off3Point, def, position });
	}
}

std::list<int> ResourceManager::GetPlayerIdsForTeam(int teamId)
{
	// first get the team short name associated with the id
	std::string teamName = "";
	std::list<int> players;

	TeamConfig team = GetTeam(teamId);
	teamName = team.shortName;

	// if there is no team with that id, return an empty list
	if (teamName.size() == 0)
	{
		return players;
	}
	// otherwise, loop through the players and grab any whose team name is the same as this one
	for (PlayerConfig player : m_playerConfigs)
	{
		if (teamName.compare(player.team) == 0)
		{
			players.push_back(player.id);
		}
	}
	return players;
	
}

const PlayerConfig& ResourceManager::GetPlayer(int playerId)
{
	for (PlayerConfig& cfg: m_playerConfigs)
	{
		if (cfg.id == playerId)
		{
			return cfg;
		}
	}
	return k_DefaultPlayerConfig;
}

const TeamConfig& ResourceManager::GetTeam(int teamId)
{
	for (TeamConfig& team : m_teamConfigs)
	{
		if (team.id == teamId)
		{
			return team;
		}
	}
	//std::list<TeamConfig>::iterator it;
	//for (it = m_teamConfigs.begin(); it != m_teamConfigs.end(); it++)
	//{
	//	if (it->id == teamId)
	//	{
	//		return *it;
	//	}
	//}
	return k_DefaultTeamConfig;
}
int ResourceManager::GetTeamCount()
{
	return m_teamConfigs.size();
}