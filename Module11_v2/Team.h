#pragma once

class AbstractTeam
{
public:
	AbstractTeam(const char* pName);
	virtual ~AbstractTeam() {}
	// every team needs a name
	const char* GetName()
	{
		return m_pName;
	}
	// purely virtual Update method
	virtual void Update() = 0;

protected:
	// useful function
	int GenerateRandomInt(int min, int max);

private:
	const char* m_pName;
};

class BasketballTeam : public AbstractTeam
{
public:
	BasketballTeam(const char* pName);
	// override the Update
	// since we don't do anything in the destructor, no need to implement it
	virtual void Update() override;
	// add a new method to get the score
	int GetScore()
	{
		return m_score;
	}
private:
	int m_score;

};
