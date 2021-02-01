// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "GameInterface.hpp"

int main()
{
    const int width = 19;
    const int height = 19;
    GameInterface g();
    int x = 0;
    while (x < 1)
    {
        Player p(5, 11, 3, 3);
        std::vector<std::vector<char>> canvas;
        for (int i = 0; i < height; i++)
        {
            std::vector<char> row;
            for (int j = 0; j < width; j++)
            {
                row.push_back('_');
            }
            canvas.push_back(row);
        }
        canvas = p.draw(canvas);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                std::cout << canvas[i][j];
            }
            std::cout << std::endl;
        }
        p.move(1, 2);
        canvas = p.draw(canvas);
        std::cout << std::endl
                  << "WOOOOOO" << std::endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                std::cout << canvas[i][j];
            }
            std::cout << std::endl;
        }
        x++;
    }
    return 0;
}