// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
// #include <list>
// #include <string>
// #include <vector>
#include <windows.h>
#include "Game.hpp"
// #include "LevelInterface.hpp"

int main()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    system("cls");
    Game g;
    g.run();
    // LevelInterface l(36);
    // l.drawCanva(5038, 5);
    // std::vector<std::vector<char>> canvas = l.getCanvas();
    // for (int i = 0; i < canvas.size(); i++)
    // {
    //     for (int j = 0; j < canvas[i].size(); j++)
    //     {
    //         std::cout << canvas[i][j];
    //     }
    //     std::cout << std::endl;
    // }
    // int a;
    // std::cin>>a;
    return 0;
}