//----------------------------------------------//
//	Author: Pavel Hranáè (xhrana02)				//
//	School: Vysoké uèení technické v Brnì		//
//	Faculty: Fakulta informaèních technologií	//
//  Date: Spring 2018                           //
//----------------------------------------------//

#include "Board.h"

using namespace std;
using namespace glm;

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
			fields[x][y] = new Field(this, x, y);
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

vector<Field*> Board::GetAllPlayFields() const
{
	auto allPlayFields = vector<Field*>();
	for (auto x = 1; x <= PlayableWidth(); x++)
	{
		for (auto y = 1; y <= PlayableHeight(); y++)
		{
			allPlayFields.push_back(fields[x][y]);
		}
	}
	return allPlayFields;
}

vector<Field*> Board::GetAllEmptyFields() const
{
	auto allEmptyFields = vector<Field*>();
	for (auto x = 1; x <= PlayableWidth(); x++)
	{
		for (auto y = 1; y <= PlayableHeight(); y++)
		{
			if(!fields[x][y]->IsFieldOccupied())
			{
				allEmptyFields.push_back(fields[x][y]);
			}
		}
	}
	return allEmptyFields;
}

vector<Field*> Board::GetAllNeighborFields(Field* field) const
{
	auto neighbors = vector<Field*>();

	auto fieldX = field->GetX();
	auto fieldY = field->GetY();

	for (auto modX = -1; modX <= 1; modX++)
	{
		for (auto modY = -1; modY <= 1; modY++)
		{
			if(modX == 0 && modY == 0)
			{
				// skip itself
				continue;
			}

			auto x = fieldX + modX;
			auto y = fieldY + modY;

			if (x < 0 || x >= ActualWidth() ||
				y < 0 || y >= ActualHeight() )
			{
				// skip non-existing fields
				continue;
			}

			neighbors.push_back(fields[x][y]);
		}
	}

	return neighbors;
}

vector<Field*> Board::GetAllNeighborPlayFields(Field* field) const
{
	auto neighbors = vector<Field*>();

	auto fieldX = field->GetX();
	auto fieldY = field->GetY();

	for (auto modX = -1; modX <= 1; modX++)
	{
		for (auto modY = -1; modY <= 1; modY++)
		{
			if(modX == 0 && modY == 0)
			{
				// skip itself
				continue;
			}

			auto x = fieldX + modX;
			auto y = fieldY + modY;

			if (x < 1 || x > PlayableWidth() ||
				y < 1 || y > PlayableHeight())
			{
				// skip non-existing and border fields
				continue;
			}

			neighbors.push_back(fields[x][y]);
		}
	}

	return neighbors;
}

vector<Field*> Board::GetAllNeighborEmptyFields(Field* field) const
{
	auto neighbors = vector<Field*>();

	auto fieldX = field->GetX();
	auto fieldY = field->GetY();

	for (auto modX = -1; modX <= 1; modX++)
	{
		for (auto modY = -1; modY <= 1; modY++)
		{
			if(modX == 0 && modY == 0)
			{
				// skip itself
				continue;
			}

			auto x = fieldX + modX;
			auto y = fieldY + modY;

			if (x < 1 || x > PlayableWidth() ||
				y < 1 || y > PlayableHeight() )
			{
				// skip non-existing and border fields
				continue;
			}

			if (fields[x][y]->IsFieldOccupied())
			{
				// skip occupied fields
				continue;
			}

			neighbors.push_back(fields[x][y]);
		}
	}

	return neighbors;
}

vector<Field*> Board::GetAllMeleeNeighborFields(Field* field) const
{
	auto neighbors = vector<Field*>();

	auto fieldX = field->GetX();
	auto fieldY = field->GetY();

	for (auto modX = -1; modX <= 1; modX++)
	{
		for (auto modY = -1; modY <= 1; modY++)
		{
			if(abs(modX) == abs(modY))
			{
				// skip itself and diagonals
				continue;
			}

			auto x = fieldX + modX;
			auto y = fieldY + modY;

			if (x < 1 || x > PlayableWidth() ||
				y < 1 || y > PlayableHeight())
			{
				// skip non-existing and border fields
				continue;
			}

			neighbors.push_back(fields[x][y]);
		}
	}

	return neighbors;
}

vector<Field*> Board::GetAllMovementNeighborFields(Field* field) const
{
	auto neighbors = vector<Field*>();

	auto fieldX = field->GetX();
	auto fieldY = field->GetY();

	for (auto modX = -1; modX <= 1; modX++)
	{
		for (auto modY = -1; modY <= 1; modY++)
		{
			if(modX == 0 && modY == 0)
			{
				// skip itself
				continue;
			}

			auto x = fieldX + modX;
			auto y = fieldY + modY;

			if (x < 1 || x > PlayableWidth() ||
				y < 1 || y > PlayableHeight() )
			{
				// skip non-existing and border fields
				continue;
			}

			if (fields[x][y]->IsFieldOccupied())
			{
				// skip occupied fields
				continue;
			}

			if (modX == 0 || modY == 0)
			{
				// perpendicular directions
				neighbors.push_back(fields[x][y]);
			}
			else
			{
				// diagonal directions
				if (!fields[x][fieldY]->IsFieldOccupied() && !fields[fieldX][y]->IsFieldOccupied())
				{
					neighbors.push_back(fields[x][y]);
				}
			}
		}
	}

	return neighbors;
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

void Board::UnhalflightAllFields()
{
	for (auto hlField : halflightedFields)
	{
		hlField->UnhalflightField();
	}
	halflightedFields = vector<Field*>();
}

void Board::HalflightFields(vector<Field*> hlFields)
{
	UnhalflightAllFields();
	for (auto hlField : hlFields)
	{
		hlField->HalflightField();
		halflightedFields.push_back(hlField);
	}
}

