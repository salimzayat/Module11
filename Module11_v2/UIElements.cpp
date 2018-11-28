#include "pch.h"
#include "UIElements.h"
#include "Defines.h"

Icon::Icon(int w, int h)
	: Renderable(w, h)
{
	m_pBuffer = new char[w * h];
	// TEST!
	for (int i = 0; i < w * h; i++)
	{
		m_pBuffer[i] = ' ';
	}
	// and add in the art

	const char pSource[4][8] = {
		{ ' ',' ','/','/','/','\\',' ',' ' },
		{ ' ',' ','|','|','o','o',' ',' ' },
		{ ' ',' ','|','|',' ','>',' ',' ' },
		{ ' ',' ',' ','\\','_',' ','-',' ' }
	};
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			int index = CalculateGridIndex(m_width, m_height, x, y);
			char c = pSource[y][x];
			m_pBuffer[index] = c;
		}
	}
}

Icon::~Icon()
{
	delete[] m_pBuffer;
}

char Icon::GetRenderChar(int x, int y)
{
	int index = CalculateGridIndex(m_width, m_height, x, y);
	return m_pBuffer[index];
}

Label::Label(int w, int h, const char* pText)
	: Renderable(w, h)
{
	m_text = std::string(pText);
}

char Label::GetRenderChar(int x, int y)
{
	// assume top oriented
 	if (y == 0)
	{
		if ((x >= 0) && (x < m_text.size()))
		{
			return m_text[x];
		}
	}
	return ' ';
}