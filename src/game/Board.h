//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Field.h"
#include <vector>

using namespace std;

class Board
{
private:
	Field*** fields;
	int playfieldHeight;
	int playfieldWidth;
public:
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
			throw std::exception(
				"Board.GetField: Coordinates are outside of the board.");
		}
		return fields[x][y];
	}

	vector<Field*> GetAllFields() const;

};
