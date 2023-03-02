#include "PieceTableHandler.h"

void PieceTableHandler::AddCharacter(char character)
{
    pieceTable.AddCharacter(character, textPosition);
    if (character == '\n')
    {
        y++;
        lineLengths.insert(lineLengths.begin() + y, 0);
        x = 0;
    }
    else
    {
        lineLengths[y] ++;
        x++;
    }
}

void PieceTableHandler::DeleteCharacter()
{
    pieceTable.DeleteCharacter(textPosition);
}

const std::string PieceTableHandler::GetText() const
{
    return pieceTable.GetText();
}

