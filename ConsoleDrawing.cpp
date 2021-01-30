#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>

BOOL ConsoleDrawing::setCursorPosition(int x, int y){
   
    COORD c; 
    c.X = x;
    c.Y = y;

    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
