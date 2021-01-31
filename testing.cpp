#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

int main(){
    ConsoleDrawing c;
    while (true){
        c.DrawBuffers();
        if(GetAsyncKeyState(VK_SPACE)){
            break;
        }
    }
    int z;
    std::cin >> z;
    return 0;
}   