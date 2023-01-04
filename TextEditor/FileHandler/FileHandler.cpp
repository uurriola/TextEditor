#include "FileHandler.h"

FileHandler FileHandler::FromFile(std::string filepath)
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
	return FileHandler(filepath, text);
}

void FileHandler::AddCharacter(char character) {
    unsigned int position = 0;
    std::string text = pieceTable.GetText();
    for (int i = 0; i < y; i++)
    {
        // TODO: that's not really efficient... text buffer should have a list of string rather than a single string
        std::size_t found = text.find_first_of('\n', position);
        if (found != std::string::npos)
        {
            position = found + 1;
        }
    }
    pieceTable.AddCharacter(character, position + x);
    x++;
};

void FileHandler::Display()
{
    std::cout << pieceTable.GetText();
}

void FileHandler::Save()
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