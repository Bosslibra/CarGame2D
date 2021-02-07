// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
// #include <list>
// #include <string>
// #include <vector>
// #include <windows.h>
#include "GameInterface.hpp"

int main()
{
    system("cls");
    GameInterface* g = new GameInterface();
    int x = 0;
    while (x<200){
        g->run();
        x++;
    }
    return 0;
}