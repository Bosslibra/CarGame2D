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
        if (coord == TOP)
        {
            std::cout << "top ";
        }
        else if (coord == LEFT)
        {
            std::cout << "left ";
        }
        else if (coord == RIGHT)
        {
            std::cout << "right ";
        }
        else if (coord == DOWN)
        {
            std::cout << "down ";
        }
        else if (coord == TOPLEFT)
        {
            std::cout << "topleft ";
        }
        else if (coord == TOPRIGHT)
        {
            std::cout << "topright ";
        }
        else if (coord == DOWNLEFT)
        {
            std::cout << "downleft ";
        }
        else if (coord == DOWNRIGHT)
        {
            std::cout << "downright ";
        }
        if (i.getMenuInput() == EXIT)
        {
            keepGoing = false;
        }
        Sleep(17);

    } while (keepGoing);

    return 0;
}