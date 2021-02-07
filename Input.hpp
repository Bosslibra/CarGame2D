
#include <windows.h>

#define STOPPED 0
#define TOP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TOPLEFT 5
#define TOPRIGHT 6
#define DOWNLEFT 7
#define DOWNRIGHT 8
#define ENTER 9

class Input
{
private:
    int x_coord;
    int y_coord;

public:
    Input();
    ~Input();
    int getMovementInput();
    int getMenuInput();
};