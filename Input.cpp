#include "Input.hpp"
#include <windows.h>

//Inizializzo con 'n' per indicare che non sta essendo premuto niente
Input::Input (){
    this->x_coord = 0;
    this->y_coord = 0;  
}

//Ritorna x, y. x è -1 per sinistra, 1 per destra. y è -1 per sotto e 1 per sopra
int Input::getKeyboardInput() {
    int coords[2] = {0, 0};
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
    //if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
      //  Input::button = 'o';
   // }
    return coords[x_coord][y_coord];
}

