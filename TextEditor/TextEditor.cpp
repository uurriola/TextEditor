#include <iostream>
#include <wchar.h>
#include <windows.h>

#include "FileHandler/FileHandler.h"

bool KeyEventProc(KEY_EVENT_RECORD, FileHandler&);


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


    std::string filepath = "C:/Users/Ulrich/source/repos/TextEditor/inputFile.txt";
    FileHandler fileHandler = FileHandler::FromFile(filepath);
    // Switch to alternate console buffer to avoid mixing file and other logs
    std::cout << "\x1b[?1049h";
    fileHandler.Display();
    std::cout << "\x1b[5 q";  // bar cursor

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
                    exit = KeyEventProc(irInBuf[i].Event.KeyEvent, fileHandler);
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
    // Switch back to main console buffer
    std::cout << "\x1b[?1049l";
    fileHandler.Save();

    SetConsoleMode(hIn, dwOriginalInMode);
    return 0;
}


bool KeyEventProc(KEY_EVENT_RECORD ker, FileHandler& fileHandler)
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
            fileHandler.DecrementY();
            break;
        case VK_DOWN:
            fileHandler.IncrementY();
            break;
        case VK_LEFT:
            fileHandler.DecrementX();
            break;
        case VK_RIGHT:
            fileHandler.IncrementX();
            break;
        case VK_BACK:
            fileHandler.DecrementX();
        case VK_DELETE:
            fileHandler.DeleteCharacter();
            fileHandler.Display();
            break;
        case VK_RETURN:
            fileHandler.AddCharacter('\n');
            fileHandler.Display();
            break;
        default:
            fileHandler.AddCharacter(ker.uChar.AsciiChar);
            fileHandler.Display();
            break;
        }
    }
    return exit;
}
