#include <chrono>
#include <iostream>
#include <map>

#include "FileHandler/ArrayHandler.h"
#include "FileHandler/PieceTableHandler.h"


int main()
{
    auto startLoadTime = std::chrono::high_resolution_clock::now();
    std::string filepath = "C:/Users/Ulrich/source/repos/TextEditor/inputFile.txt";

    std::string text;
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
    auto endLoadTime = std::chrono::high_resolution_clock::now();
    auto loadFileDuration = duration_cast<std::chrono::microseconds>(endLoadTime - startLoadTime);
    std::cout << "File loaded in " << loadFileDuration.count() / 1000.0 << "ms" << std::endl;

    std::map<std::string, FileHandler*> fileHandlers = {
        {"piece table", new PieceTableHandler(filepath, text)},
        {"raw string", new ArrayHandler(filepath, text)},
    };

    unsigned int updateCount = 1000;
    std::list<std::pair<std::pair<int, int>, char>> randomUpdates;

    // Generate random updates to apply (only insertion for now)
    for (unsigned int i = 0; i < updateCount; i++)
    {
        char cch = 'a' + rand() % 26;
        unsigned int y = rand() % 100;
        unsigned int x = rand() % 100;
        randomUpdates.push_back({ {x, y}, cch });
    }

    for (auto [handlerName, fileHandler] : fileHandlers)
    {
        std::cout << handlerName << std::endl;
        // fileHandler.Display();

        auto startUpdatesTime = std::chrono::high_resolution_clock::now();
        for (auto [position, characterToInsert] : randomUpdates)
        {
            fileHandler->SetPosition(position.first, position.second);
            fileHandler->AddCharacter(characterToInsert);
        }

        auto endUpdatesTime = std::chrono::high_resolution_clock::now();
        auto updateFileDuration = duration_cast<std::chrono::microseconds>(endUpdatesTime - startUpdatesTime);
        std::cout << "Inserted " << randomUpdates.size() << " characters in " << updateFileDuration.count() / 1000.0 << "ms." << std::endl;

        auto startSaveTime = std::chrono::high_resolution_clock::now();
        fileHandler->Save();
        auto endSaveTime = std::chrono::high_resolution_clock::now();
        auto saveFileDuration = duration_cast<std::chrono::microseconds>(endSaveTime - startSaveTime);
        std::cout << "File saved in " << saveFileDuration.count() / 1000.0 << "ms." << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
