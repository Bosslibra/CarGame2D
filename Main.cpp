// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
// #include <list>
// #include <string>
// #include <vector>
#include <windows.h>
#include "Game.hpp"
#include "ConsoleDrawing.hpp"

int main()
{  
    
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    system("cls");
    Game g;
    g.run();
    return 0;
}