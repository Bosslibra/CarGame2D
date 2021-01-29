#include <iostream>
#include "Input.hpp"
#include <windows.h>

int main(){
	Input i;
    int keepGoing = 0;

    do {
        int coord = i.getKeyboardInput();

        if (coord == 1){
            std::cout << "top ";
        } else if (coord == 2){
            std::cout << "left ";
        }else if (coord == 3){
            std::cout << "right ";
        }else if (coord == 4){
            std::cout << "down ";
        }else if (coord == 5){
            std::cout << "topleft ";
        }else if (coord == 6){
            std::cout << "topright ";
        }else if (coord == 7){
            std::cout << "downleft ";
        }else if (coord == 8){
            std::cout << "downright ";
        }

        keepGoing++;

        Sleep(17);

    } while (keepGoing < 900);

    return 0;
}