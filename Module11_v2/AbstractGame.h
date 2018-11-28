#pragma once
class AbstractGame
{
public:
	AbstractGame();
	// virtual destructor.  needed for any abstract class
	virtual ~AbstractGame();
	// simulate the game in its entirety
	void Run();
	
protected:
	// initialize the start conditions
	virtual void Initialize() = 0;
	// step through the game for one loop
	virtual void Step() = 0;
	// returns whether or not the game is over
	virtual bool IsOver() = 0;
	// render out the current game state
	virtual void Render() = 0;
	// and for completeness sake
	virtual void Shutdown() = 0;

};

