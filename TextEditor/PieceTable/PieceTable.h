#pragma once

#include <list>
#include <string>

class TableEntry
{
public:
	TableEntry(std::string buf, unsigned int startI, unsigned int si) : buffer(buf), startIndex(startI), size(si) {};

	std::string buffer;
	unsigned int startIndex;
	unsigned int size;
};

class PieceTable
{
public:
	void Add(std::string content);
	void Add(std::string content, unsigned int position);
	std::string GetText();
private:
	std::list<TableEntry> blocks;
};

