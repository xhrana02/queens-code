//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Field.h"
#include <vector>
#include <glm/glm.hpp>

class Board
{
private:
	Field*** fields;
	int playfieldHeight;
	int playfieldWidth;

	std::vector<Field*> highlightedFields = std::vector<Field*>();
public:
	~Board();
	Board(int width, int height);

	int PlayableHeight() const
	{
		return playfieldHeight;
	}
	int PlayableWidth() const
	{
		return playfieldWidth;
	}

	int ActualHeight() const
	{
		return playfieldHeight + 2;
	}
	int ActualWidth() const
	{
		return playfieldWidth + 2;
	}

	Field* GetField(int x, int y) const
	{
		if (x < 0 || x >= ActualWidth() ||
			y < 0 || y >= ActualHeight())
		{
			return nullptr;
		}
		return fields[x][y];
	}

	Field* GetPlayField(int x, int y) const
	{
		if (x < 1 || x > PlayableWidth() ||
			y < 1 || y > PlayableHeight())
		{
			return nullptr;
		}
		return fields[x][y];
	}

	Field* GetFieldFromMouse(glm::vec2 mouse) const;
	Field* GetPlayFieldFromMouse(glm::vec2 mouse) const;

	std::vector<Field*> GetAllFields() const;
	std::vector<Field*> GetAllPlayFields() const;
	std::vector<Field*> GetAllEmptyFields() const;

	std::vector<Field*> GetAllNeighborFields(Field* field) const;
	std::vector<Field*> GetAllNeighborPlayFields(Field* field) const;
	std::vector<Field*> GetAllNeighborEmptyFields(Field* field) const;

	void UnhighlightAllFields();
	void HighlightField(Field* hlField);
	void HighlightFields(std::vector<Field*> hlFields);
};
