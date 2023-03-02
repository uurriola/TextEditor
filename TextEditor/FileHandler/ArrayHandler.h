#pragma once

#include <array>

#include "FileHandler.h"

class ArrayHandler: public FileHandler
{
public:
	ArrayHandler(std::string filePath, std::string content) : FileHandler(filePath, content), rawString(content) {}

	virtual void AddCharacter(char character) override;
	virtual void DeleteCharacter() override;
	virtual const std::string GetText() const override;

private:
	std::string rawString;
};

