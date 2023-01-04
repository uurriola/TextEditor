#include "PieceTable.h"


void PieceTable::AddCharacter(char character, unsigned int position)
{
	updateBuffer->text += character;

	// How to know if we are updating the same block as before? well if it is the last block
	TableEntry entry(updateBuffer, updateBuffer->length() - 1, 1);

	unsigned int blockEndPosition = 0;
	bool splitBlock = false;
	std::list<TableEntry>::iterator blockIt = blocks.begin();
	while (blockIt != blocks.end())
	{
		if (blockEndPosition + blockIt->size >= position)
		{
			TableEntry entryToSplit = *blockIt;
			if (entryToSplit.buffer == updateBuffer && (entryToSplit.startIndex + entryToSplit.size == entryToSplit.buffer->length() - 1) && (position == blockEndPosition + entryToSplit.size))
			{
				// Add a character to last block
				blockIt->size++;
			}
			else
			{
				// Create a new block in the middle
				unsigned int firstPartSize = position - blockEndPosition;
				if (firstPartSize > 0)
				{
					TableEntry firstPartEntry(entryToSplit.buffer, entryToSplit.startIndex, firstPartSize);
					blocks.insert(blockIt, firstPartEntry);
				}
				blocks.insert(blockIt, entry);
				// This action is not necessary if we did not have a first entry
				if (firstPartSize > 0)
				{
					if (entryToSplit.size - firstPartSize > 0)
					{
						TableEntry secondPartEntry(entryToSplit.buffer, entryToSplit.startIndex + firstPartSize, entryToSplit.size - firstPartSize);
						blocks.insert(blockIt, secondPartEntry);
					}
					blocks.erase(blockIt);
				}
			}

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
		text += block.buffer->substr(block.startIndex, block.size);
	}
	return text;
}