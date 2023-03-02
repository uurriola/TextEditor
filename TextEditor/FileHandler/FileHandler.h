#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../PieceTable/PieceTable.h"

class FileHandler
{
public:
	FileHandler(std::string filepath, const std::string_view content): x(0), y(0), textPosition(0), filepath(filepath)
	{
		size_t previous_found{ 0 };
		size_t found = content.find_first_of('\n');
		while (found != std::string::npos)
		{
			lineLengths.push_back(found - previous_found);
			previous_found = found + 1;
			found = content.find_first_of('\n', found + 1);
		}
		lineLengths.push_back(content.length() - previous_found);
	};

	virtual ~FileHandler() {};

	virtual void AddCharacter(const char character) = 0;
	virtual void DeleteCharacter() = 0;

	void Display() const;
	virtual const std::string GetText() const = 0;
	void Save() const;

	void SetPosition(const unsigned int nx, const unsigned int ny);
protected:
	unsigned int x, y, textPosition;
	std::vector<unsigned int> lineLengths;

private:
	std::string filepath;
};

