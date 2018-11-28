#pragma once
#include "AbstractGame.h"
#include "Team.h"


class BasketballGame :
	public AbstractGame
{
public:
	BasketballGame();
	virtual ~BasketballGame();

protected:
	virtual void Initialize() override;
	virtual void Step() override;
	virtual bool IsOver() override;
	virtual void Render() override;
	virtual void Shutdown() override;

private:
	BasketballTeam* m_pTeam1;
	BasketballTeam* m_pTeam2;
};

