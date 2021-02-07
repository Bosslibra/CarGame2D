#include "Input.hpp"
#include <windows.h>

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

Input::Input()
{
}

int Input::getMovementInput()
{

    //Detects Keystrokes
    if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)))
    {
        return INPUT_TOPLEFT;
    }
    else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))
    {
        return INPUT_OPPOSITE;
    }
    else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)))
    {
        return INPUT_TOPRIGHT;
    }
    else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)))
    {
        return INPUT_DOWNLEFT;
    }
    else if ((GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)))
    {
        return INPUT_DOWNRIGHT;
    }
    else if ((GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT)) && (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT)))
    {
        return INPUT_OPPOSITE;
    }
    else if ((GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP)) && (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN)))
    {
        return INPUT_OPPOSITE;
    }
    else if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))
    {
        return INPUT_TOP;
    }
    else if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))
    {
        return INPUT_LEFT;
    }
    else if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))
    {
        return INPUT_DOWN;
    }
    else if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))
    {
        return INPUT_RIGHT;
    }
}

//Returns 9 if either Spacebar or Enter are pressed
int Input::getMenuInput()
{
    if (GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_SPACE))
    {
        return INPUT_EXIT;
    }
}