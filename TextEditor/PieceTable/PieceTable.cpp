#include "PieceTable.h"

void PieceTable::Add(std::string content)
{
	TableEntry entry(content, 0, content.length());
	blocks.push_back(entry);
}

void PieceTable::Add(std::string content, unsigned int position)
{
	TableEntry entry(content, 0, content.length());
	unsigned int blockEndPosition = 0;
	bool splitBlock = false;
	std::list<TableEntry>::iterator blockIt = blocks.begin();
	while (blockIt != blocks.end())
	{
		if (blockEndPosition + blockIt->size > position)
		{
			TableEntry entryToSplit = *blockIt;
			unsigned int firstPartSize = position - blockEndPosition;
			if (firstPartSize > 0)
			{
				TableEntry firstPartEntry(entryToSplit.buffer, entryToSplit.startIndex, firstPartSize);
				blocks.insert(blockIt, firstPartEntry);
			}
			blocks.insert(blockIt, entry);
			if (entryToSplit.size - firstPartSize > 0)
			{
				TableEntry secondPartEntry(entryToSplit.buffer, entryToSplit.startIndex + firstPartSize, entryToSplit.size - firstPartSize);
				blocks.insert(blockIt, secondPartEntry);
			}
			blocks.erase(blockIt);
			return;
		}
		blockEndPosition += blockIt->size;
		++blockIt;
	}

	blocks.insert(blockIt, entry);

}

std::string PieceTable::GetText()
{
	std::string text = "";
	for (auto& block : blocks)
	{
		text += block.buffer.substr(block.startIndex, block.size);
	}
	return text;
}