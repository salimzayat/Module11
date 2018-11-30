#include "pch.h"
#include "Factory.h"

#include "ResourceManager.h"

BasketballTeam* Factory::GetTeam(int teamId)
{
	// get the config for that teamId
	const TeamConfig& cfg = ResourceManager::GetInst()->GetTeam(teamId);
	BasketballTeam* pTeam = new BasketballTeam(cfg.id, cfg.name.c_str(), cfg.city.c_str(), cfg.shortName.c_str());
	return pTeam;
}

Player* Factory::GetPlayer(int playerId)
{
	// we need the player with that id
	const PlayerConfig& cfg = ResourceManager::GetInst()->GetPlayer(playerId);
	// now configure that player object
	Player* pPlayer = new Player(cfg.id, cfg.name.c_str(), cfg.position);
	pPlayer->GetShootingComponent()->SetRatings(cfg.offense2Point, cfg.offense3Point);
	pPlayer->GetDefenseComponent()->SetRating(cfg.defense);
	return pPlayer;
}