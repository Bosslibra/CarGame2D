#include <iostream>
#include "Input.hpp"
#include <windows.h>

int main(){

    do {
        if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)){
            std::cout << "up ";
        } else if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)){
            std::cout << "left ";
        } else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)){
            std::cout << "right ";
        } else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)){
            std::cout << "down ";
        } else if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
            std::cout << "0 ";
        }
        

    } while (true);

    

    return 0;
}
