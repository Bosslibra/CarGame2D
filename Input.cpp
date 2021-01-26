#include "Input.hpp"
#include <windows.h>

//Inizializzo con 'n' per indicare che non sta essendo premuto niente
Input::Input (char button){
    button = 'n';
}

//W, A, S, D e le frecce direzionali sono equivalenti. Spazio e Enter sono equivalenti
char Input::getKeyboardInput() {
    if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)){
        this->button = 'w';
    } else if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)){
        this->button = 'a';
    } else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)){
        this->button = 's';
    } else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)){
        this->button = 'd';
    } else if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
        this->button = 'o';
    }
    return this->button;
}

