//----------------------------------------------//
//  Author: Pavel Hranáè (xhrana02)             //
//  School: Vysoké uèení technické v Brnì       //
//  Faculty: Fakulta informaèních technologií   //
//  Date: Spring 2018                           //
//----------------------------------------------//

#pragma once
#include "Field.h"
#include <vector>
#include <glm/glm.hpp>

class Board
{
protected:
    Field*** fields;
    int playfieldHeight;
    int playfieldWidth;

	Field* throneField = nullptr;
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

	Field* GetField(int x, int y) const;
	Field* GetPlayField(int x, int y) const;
	Field* GetThroneField() const;
	void SetThroneField(int x, int y);

    Field* GetFieldFromMouse(glm::vec2 mouse) const;
    Field* GetPlayFieldFromMouse(glm::vec2 mouse) const;

    std::vector<Field*> GetAllFields() const;
    std::vector<Field*> GetAllPlayFields() const;
    std::vector<Field*> GetAllEmptyFields() const;

    std::vector<Field*> GetAllNeighborPlayFields(Field* field) const;
    std::vector<Field*> GetAllNeighborEmptyFields(Field* field) const;

    std::vector<Field*> GetAllMeleeNeighborFields(Field* field) const;
    std::vector<Field*> GetAllMovementNeighborFields(Field* field) const;

    void UnhighlightAllFields();
    void HighlightField(Field* hlField);
    void HighlightFields(std::vector<Field*> hlFields);
    std::vector<Field*> GetAllHighlightedFields() const
    {
        return highlightedFields;
    }

    void UnhalflightAllFields() const;
    void HalflightFields(std::vector<Field*> hlFields) const;
};
