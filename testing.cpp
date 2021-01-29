//#include "Input.hpp"
#include <iostream>
#include <windows.h>

#define TOP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TOPLEFT 5
#define TOPRIGHT 6
#define DOWNLEFT 7
#define DOWNRIGHT 8
#define ENTER 9


class Input {
    private:
        int x_coord;
        int y_coord;


    public:
        int getMovementInput();
        int getMenuInput();
};

int Input::getMovementInput() {

    //Detects Keystrokes
    if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))){
        return TOPLEFT;
    } else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))){
        return TOPRIGHT;
    } else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))){
       return DOWNLEFT;
    } else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))){
       return DOWNRIGHT;
    } else if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)){
        return TOP;
    } else if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)){
        return LEFT;
    } else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)){
    	return DOWN;
    } else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)){
    	return RIGHT;
    }
}
int Input::getMenuInput() {
     if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
        return ENTER;
    }
}

int main(){
	Input i;
    bool keepGoing = true;

    do {
        int coord = i.getMovementInput();
        if (coord == 1){
            std::cout << "top ";
        } else if (coord == 2){
            std::cout << "left ";
        }else if (coord == 3){
            std::cout << "right ";
        } else if (coord == 4){
            std::cout << "down ";
        } else if (coord == 5){
            std::cout << "topleft ";
        } else if (coord == 6){
            std::cout << "topright ";
        } else if (coord == 7){
            std::cout << "downleft ";
        } else if (coord == 8){
            std::cout << "downright ";
        }
        if (i.getMenuInput() == 9){
            keepGoing = false;
        }
        Sleep(17);

    } while (keepGoing);

    return 0;
}