#include "pch.h"
#include "RenderBuffer.h"
#include <iostream>

RenderBuffer::RenderBuffer(int w, int h)
	: m_height(h)
	, m_width(w)
{
	m_pGrid = new char[w * h];
	for (int i = 0; i < w * h; i++)
	{
		m_pGrid[i] = '.';
	}
}


RenderBuffer::~RenderBuffer()
{
	delete[] m_pGrid;
}

int RenderBuffer::CalculateIndex(int x, int y)
{
	return CalculateGridIndex(m_width, m_height, x, y);
}

void RenderBuffer::AddToBuffer(Point2d position, Renderable* pRenderable)
{
	m_renderablesAndPositions[pRenderable] = position;
}

void RenderBuffer::Update()
{
	std::map<Renderable*, Point2d>::iterator it;
	for (it = m_renderablesAndPositions.begin(); it != m_renderablesAndPositions.end(); it++)
	{
		Renderable* pRenderable = it->first;
		Point2d position = it->second;
		for (int y = 0; y < pRenderable->GetRenderHeight(); y++)
		{
			for (int x = 0; x < pRenderable->GetRenderWidth(); x++)
			{
				int index = CalculateIndex(x + position.x, y + position.y);
				m_pGrid[index] = pRenderable->GetRenderChar(x, y);
			}
		}
	}
}

void RenderBuffer::Render()
{
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			std::cout << m_pGrid[CalculateIndex(x, y)];
		}
		std::cout << std::endl;
	}
}