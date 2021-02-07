#include "Input.cpp"
#include <iostream>
#include <windows.h>

int main()
{
    Input i;
    bool keepGoing = true;

    do
    {
        int coord = i.getMovementInput();
        if (coord == INPUT_TOP)
        {
            std::cout << "top ";
        }
        else if (coord == INPUT_LEFT)
        {
            std::cout << "left ";
        }
        else if (coord == INPUT_RIGHT)
        {
            std::cout << "right ";
        }
        else if (coord == INPUT_DOWN)
        {
            std::cout << "down ";
        }
        else if (coord == INPUT_TOPLEFT)
        {
            std::cout << "topleft ";
        }
        else if (coord == INPUT_TOPRIGHT)
        {
            std::cout << "topright ";
        }
        else if (coord == INPUT_DOWNLEFT)
        {
            std::cout << "downleft ";
        }
        else if (coord == INPUT_DOWNRIGHT)
        {
            std::cout << "downright ";
        }
        if (i.getMenuInput() == INPUT_EXIT)
        {
            keepGoing = false;
        }
        Sleep(17);

    } while (keepGoing);

    return 0;
}