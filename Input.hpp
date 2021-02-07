#pragma once

#define INPUT_OPPOSITE 0
#define INPUT_TOP 1
#define INPUT_LEFT 2
#define INPUT_RIGHT 3
#define INPUT_DOWN 4
#define INPUT_TOPLEFT 5
#define INPUT_TOPRIGHT 6
#define INPUT_DOWNLEFT 7
#define INPUT_DOWNRIGHT 8
#define INPUT_EXIT 9

class Input
{
private:
    int x_coord;
    int y_coord;

public:
    Input();
    int getMovementInput();
    int getMenuInput();
};