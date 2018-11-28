#pragma once

#include "Defines.h"
#include "Renderable.h"
#include <map>

class RenderBuffer
{
public:
	RenderBuffer(int w, int h);
	~RenderBuffer();

	void AddToBuffer(Point2d position, Renderable* pRenderable);

	void Render();
	void Update();
private:
	int CalculateIndex(int x, int y);

	
	char* m_pGrid;
	int m_width;
	int m_height;

	std::map<Renderable*, Point2d> m_renderablesAndPositions;
};

