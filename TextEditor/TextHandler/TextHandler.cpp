#include "TextHandler.h"

TextHandler TextHandler::FromFile(std::string filepath)
{
    std::string text = "";

    std::ifstream file;
    file.open(filepath);
    if (file.is_open()) {
        while (std::getline(file, text, '\0'))
        {
            continue;
        }
        file.close();
    }
    else {
        std::cerr << "Couldn't open file\n";
    }
	return TextHandler(filepath, text);
}

void TextHandler::Add(std::string text, unsigned int position)
{
    pieceTable.Add(text, position);
}

void TextHandler::Display()
{
    std::cout << pieceTable.GetText();
}

void TextHandler::Save()
{
    std::ofstream file;
    file.open(filepath);
    if (file.is_open()) {
        file << pieceTable.GetText();
        file.close();
    }
    else {
        std::cerr << "Couldn't open file\n";
    }
}