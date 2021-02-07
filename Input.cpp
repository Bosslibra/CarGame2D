#include "Input.hpp"


Input::Input(){}
Input::~Input(){}

/*Returns:
- 0 if both Up and Down or both Left and Right are pressed simultaneously
- 1 if Up (W) is pressed
- 2 if Left (A) is pressed
- 3 if Right (D) is pressed
- 4 if Down (S) is pressed
- 5 if both Up (W) and Left (A) are pressed
- 6 if both Up (W) and Right (D) are pressed
- 7 if both Down (S) and Left (A) are pressed
- 8 if both Down (S) and Right (D) is pressed
*/
int Input::getMovementInput() {

    //Detects Keystrokes
    if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))){
        return TOPLEFT;
    } else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))){
        return STOPPED;
    } else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))){
        return TOPRIGHT;
    } else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))){
       return DOWNLEFT;
    } else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))){
       return DOWNRIGHT;
    } else if ((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))){
        return STOPPED;
    } else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))){
        return STOPPED;
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

//Returns 9 if either Spacebar or Enter are pressed
int Input::getMenuInput(){
    if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE)){
        return ENTER;
    }
}