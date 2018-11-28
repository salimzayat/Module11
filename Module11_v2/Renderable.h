#pragma once

class Renderable
{
public:
	Renderable(int w, int h)
		: m_width(w)
		, m_height(h)
	{

	}

	virtual ~Renderable() {}

	virtual int GetRenderWidth() { return m_width; }
	virtual int GetRenderHeight() { return m_height; }

	virtual char GetRenderChar(int x, int y) = 0;
protected:
	int m_width;
	int m_height;
};