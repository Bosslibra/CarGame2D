// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
#include <list>
#include <string>
#include "GameInterface.hpp"

int main()
{
    const int width = 300;
    const int height = 300;
    GameInterface g();
    int x = 0;
    while (x < 2)
    {
        Player p(300, 3, 3, 3);
        char canvas[height][width];
        p.draw(canvas);
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                canvas[i][j] = ' ';
                if (i == p.getY() && x == p.getY())
            }
        }
        p.move(1, 3);
        x++;
    }
    return 0;
}