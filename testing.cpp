#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>

int main(){
    COORD c = {22, 22};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    std::cout << "#";
    int z;
    std::cin>> z;
    return 0;
}