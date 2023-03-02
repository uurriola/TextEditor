#pragma once

#include <list>
#include <memory>
#include <string>

#include "../TextBuffer/TextBuffer.h"


class TableEntry
{
public:
	TableEntry(std::shared_ptr<TextBuffer> buf, unsigned int startI, unsigned int si) : buffer(buf), startIndex(startI), size(si) {};

	std::shared_ptr<TextBuffer> buffer;
	unsigned int startIndex;
	unsigned int size;
};

class PieceTable
{
public:
	PieceTable(std::string content)
	{
		originBuffer = std::make_shared<TextBuffer>(content);
		updateBuffer = std::make_shared<TextBuffer>("");

		TableEntry entry(originBuffer, 0, originBuffer->length());
		blocks.push_back(entry);
	}

	void AddCharacter(char character, unsigned int position);
	void DeleteCharacter(unsigned int position);

	const std::string GetText() const;
private:
	std::shared_ptr<TextBuffer> originBuffer;
	std::shared_ptr<TextBuffer> updateBuffer;
	std::list<TableEntry> blocks;
};

