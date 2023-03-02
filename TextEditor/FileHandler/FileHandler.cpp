#include "FileHandler.h"


void FileHandler::Display() const
{
    std::cout << GetText();
}

void FileHandler::Save() const
{
    std::ofstream file;
    file.open(filepath);
    if (file.is_open()) {
        file << GetText();
        file.close();
    }
    else {
        std::cerr << "Couldn't open file\n";
    }
}

void FileHandler::SetPosition(unsigned int nx, unsigned int ny)
{
    y = (ny < lineLengths.size()) ? ny : lineLengths.size() - 1;
    x = (nx < lineLengths[y]) ? nx : lineLengths[y] - 1;

    textPosition = 0;
    for (unsigned int i = 0; i < y; i++)
    {
        textPosition = lineLengths[i] + 1;
    }
    textPosition += x;
}
