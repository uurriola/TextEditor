#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../PieceTable/PieceTable.h"

class FileHandler
{
public:
	static FileHandler FromFile(std::string filepath);
	FileHandler(std::string filepath, std::string content): x(0), y(0), filepath(filepath), pieceTable(content)
	{
		std::string text = pieceTable.GetText();
		size_t previous_found{ 0 };
		size_t found = text.find_first_of('\n');
		while (found != std::string::npos)
		{
			lineLengths.push_back(found - previous_found);
			previous_found = found + 1;
			found = text.find_first_of('\n', found + 1);
		}
		lineLengths.push_back(text.length() - previous_found);
	};

	void AddCharacter(char character);
	void DeleteCharacter();

	void Display();
	void Save();

	// TODO: handle line length in the following methods
	void IncrementX()
	{
		if (x < lineLengths[y])
		{
			x++;
			std::cout << "\x1b[1C";
		}
	}
	void DecrementX() {
		if (x > 0)
		{
			x--;
			std::cout << "\x1b[1D";
		}
	}
	void IncrementY()
	{
		if (y < lineLengths.size())
		{
			y++;
			std::cout << "\x1b[1B";
		}
	}
	void DecrementY()
	{
		if (y > 0)
		{
			y--;
			std::cout << "\x1b[1A";
		}
	}

	const unsigned int X() { return x; }
	const unsigned int Y() { return y; }
private:
	unsigned int x, y;
	std::vector<unsigned int> lineLengths;
	std::string filepath;
	PieceTable pieceTable;
};

