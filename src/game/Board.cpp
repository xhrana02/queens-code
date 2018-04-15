//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Board.h"

/**
 * \brief Board class constructor.
 * 
 * Generates a new board with playing field size determined by parameters height and width.
 * Actual height and width of the board include border fields on each side.
 */
Board::Board(int width, int height)
{
	if(width < 1 || height < 1)
	{
		throw std::exception(
			"Board.ctor: Invalid board size.");
	}

	playfieldWidth = width;
	playfieldHeight = height;

	fields = new Field**[ActualWidth()];
	for (auto x = 0; x < ActualWidth(); x++)
	{
		fields[x] = new Field*[ActualHeight()];
		for (auto y = 0; y < ActualHeight(); y++)
		{
			auto newFieldTerrain = Empty;
			if (x == 0 || x == ActualWidth() - 1 ||
			    y == 0 || y == ActualHeight() - 1)
			{
				newFieldTerrain = Border;
			}
			fields[x][y] = new Field(x, y, newFieldTerrain);
		}
	}

}

vector<Field*> Board::GetAllFields() const
{
	auto allFields = vector<Field*>();
	for (auto x = 0; x < ActualWidth(); x++)
	{
		for (auto y = 0; y < ActualHeight(); y++)
		{
			allFields.push_back(fields[x][y]);
		}
	}
	return allFields;
}

