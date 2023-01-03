#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <wchar.h>
#include <windows.h>

bool KeyEventProc(KEY_EVENT_RECORD);


int main()
{
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        return -1;
    }

    DWORD dwInMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return -1;
    }

    std::cout << "\x1b[5 q";

    std::string filename = "../inputFile.txt";
    std::string fileContent;

    std::ifstream myfile;
    myfile.open(filename);
    if (myfile.is_open()) {
        while (std::getline(myfile, fileContent))
        {
            std::cout << fileContent;
        }
        myfile.close();
    }
    else {
        std::cerr << "Couldn't open file\n";
    }

    std::cout << "\x1b[0;0f";

    const int bufferSize = 10;
    INPUT_RECORD irInBuf[bufferSize];
    DWORD cNumRead;

    bool exit = false;
    while (!exit)
    {
        if (!ReadConsoleInput(hIn, irInBuf, bufferSize, &cNumRead))
        {
            std::cout << "ReadConsoleInput";
        }
        else
        {
            for (unsigned int i = 0; i < cNumRead; i++)
            {
                switch (irInBuf[i].EventType)
                {
                case KEY_EVENT: // keyboard input
                    exit = KeyEventProc(irInBuf[i].Event.KeyEvent);
                    break;
                case MOUSE_EVENT:
                case WINDOW_BUFFER_SIZE_EVENT:
                case FOCUS_EVENT:
                case MENU_EVENT:
                    break;
                default:
                    std::cout << "Unknown event type";
                    break;
                }
            }
        }
    }

    std::cout << "\x1b[u";
    SetConsoleMode(hIn, dwOriginalInMode);
    return 0;
}

bool KeyEventProc(KEY_EVENT_RECORD ker)
{
    bool exit = false;
    if (ker.bKeyDown)
    {
        switch (ker.wVirtualKeyCode)
        {
        case VK_ESCAPE:
            exit = true;
            break;
        case VK_UP:
            std::cout << "\x1b[1A";
            break;
        case VK_DOWN:
            std::cout << "\x1b[1B";
            break;
        case VK_LEFT:
            std::cout << "\x1b[1D";
            break;
        case VK_RIGHT:
            std::cout << "\x1b[1C";
            break;
        case VK_RETURN:
            std::cout << "\x1b[1L";
            break;
        default:
            size_t charCount = wcslen(&ker.uChar.UnicodeChar) - 1;
            std::wcout << "\x1b[" << charCount << "@" << ker.uChar.UnicodeChar;
            break;
        }
    }
    return exit;

}
