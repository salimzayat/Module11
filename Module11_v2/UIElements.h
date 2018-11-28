#pragma once
#include "Renderable.h"
#include "Player.h"
#include <string>

class Icon : public Renderable
{
public:
	Icon(int w, int h);
	virtual ~Icon();
		

	virtual char GetRenderChar(int x, int y) override;

private:
	char* m_pBuffer;
};

class Label : public Renderable
{
public:
	Label(int w, int h, const char* pText);

	virtual char GetRenderChar(int x, int y) override;
	
private:
	std::string m_text;
};