#include "Input.hpp"
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

//Inizializzo con 'n' per indicare che non sta essendo premuto niente
Input::Input(){
    this->x_coord = 0;
    this->y_coord = 0;  
}

int Input::getKeyboardInput() {
    int coordinates_combined = 0;

    //Detects Keystrokes
    if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)){
        Input::y_coord += 1;
    }
    if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)){
        Input::x_coord -= 1;
    }
    if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)){
        Input::y_coord -= 1;
    }
    if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)){
        Input::x_coord += 1;
    }
    if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
        coordinates_combined = ENTER;
    }

    //Determines Output
    if (Input::x_coord == 0 && Input::y_coord == 1){
        coordinates_combined = TOP;
    } else if (Input::x_coord == -1 && Input::y_coord == 0){
        coordinates_combined = LEFT;
    } else if (Input::x_coord == 1 && Input::y_coord == 0){
        coordinates_combined = RIGHT;
    } else if (Input::x_coord == 0 && Input::y_coord == -1){
        coordinates_combined = DOWN;
    } else if (Input::x_coord == -1 && Input::y_coord == 1){
        coordinates_combined = TOPLEFT;
    } else if (Input::x_coord == 1 && Input::y_coord == 1){
        coordinates_combined = TOPRIGHT;
    } else if (Input::x_coord == -1 && Input::y_coord == -1){
        coordinates_combined = DOWNLEFT;
    } else if (Input::x_coord == 1 && Input::y_coord == -1){
        coordinates_combined = DOWNRIGHT;
    }

    return (coordinates_combined);
}

