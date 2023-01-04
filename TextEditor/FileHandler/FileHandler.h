#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "../PieceTable/PieceTable.h"

class FileHandler
{
public:
	static FileHandler FromFile(std::string filepath);
	FileHandler(std::string filepath, std::string content): x(0), y(0), filepath(filepath), pieceTable(content) {};

	void AddCharacter(char character);

	void Display();
	void Save();

	// TODO: handle line length in the following methods
	void IncrementX() { x++; }
	void DecrementX() { if (x > 0)x--; }
	void IncrementY() { y++; }
	void DecrementY() { if (y > 0)y--; }
private:
	unsigned int x, y;
	std::string filepath;
	PieceTable pieceTable;
};

