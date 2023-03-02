#pragma once

#include "FileHandler.h"

class PieceTableHandler: public FileHandler
{
public:
	PieceTableHandler(std::string filePath, std::string content) : FileHandler(filePath, content), pieceTable(content) {}

	virtual void AddCharacter(char character) override;
	virtual void DeleteCharacter() override;
	virtual const std::string GetText() const override;

private:
	PieceTable pieceTable;
};

