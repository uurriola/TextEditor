#include "ArrayHandler.h"

void ArrayHandler::AddCharacter(char character)
{
	rawString.insert(rawString.begin() + textPosition, character);
}

void ArrayHandler::DeleteCharacter()
{
	rawString.erase(rawString.begin() + textPosition);
}

const std::string ArrayHandler::GetText() const
{
	return rawString;
}
