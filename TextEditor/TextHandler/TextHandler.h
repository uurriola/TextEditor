#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "../PieceTable/PieceTable.h"

class TextHandler
{
public:
	static TextHandler FromFile(std::string filepath);
	TextHandler(std::string filepath, std::string content): filepath(filepath) { pieceTable.Add(content); };

	void Add(std::string text, unsigned int position);
	void Display();
	void Save();
private:
	std::string filepath;
	PieceTable pieceTable;
};

