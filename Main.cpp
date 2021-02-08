#include <windows.h>
#include "Game.hpp"


int main()
{
    //imposto la finestra a schermo intero
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    system("cls");
    Game g;
    g.run();
    return 0;
}