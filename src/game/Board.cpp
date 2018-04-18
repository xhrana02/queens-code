//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Board.h"

Board::~Board()
{
	for (auto x = 0; x < ActualWidth(); x++)
	{
		for (auto y = 0; y < ActualHeight(); y++)
		{
			if(fields[x][y] != nullptr)
			{
				delete fields[x][y];
			}
		}
	}
}

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
			fields[x][y] = new Field(x, y);
			if (x == 0 || x == ActualWidth() - 1 ||
			    y == 0 || y == ActualHeight() - 1)
			{
				fields[x][y]->SetTerrainType(Border);
			}
		}
	}
}

Field* Board::GetFieldFromMouse(vec2 mouse) const
{
	auto fieldX = int(round(mouse.x + ActualWidth() / 2.f));
	auto fieldY = int(round(mouse.y + ActualHeight() / 2.f));
	return GetField(fieldX, fieldY);
}

Field* Board::GetPlayFieldFromMouse(vec2 mouse) const
{
	auto fieldX = int(round(0.5 + mouse.x + PlayableWidth() / 2.f));
	auto fieldY = int(round(0.5 + mouse.y + PlayableHeight() / 2.f));
	return GetPlayField(fieldX, fieldY);
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

void Board::UnhighlightAllFields()
{
	for (auto hlField : highlightedFields)
	{
		hlField->UnhighlightField();
	}
	highlightedFields = vector<Field*>();
}

void Board::HighlightField(Field* hlField)
{
	UnhighlightAllFields();
	hlField->HighlightField();
	highlightedFields.push_back(hlField);
}

void Board::HighlightFields(vector<Field*> hlFields)
{
	UnhighlightAllFields();
	for (auto hlField : hlFields)
	{
		hlField->HighlightField();
		highlightedFields.push_back(hlField);
	}
}

