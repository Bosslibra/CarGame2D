#include "Sprite.hpp"
#include <list>
#include <string>
#include <iostream>
Sprite::Sprite()
{
}
Sprite::~Sprite()
{
}
void Sprite::addLine(std::string line)
{
    this->sprite.push_back(line);
}

std::vector<std::vector<char>> Sprite::draw(std::vector<std::vector<char>> canvas, int x, int y, int width, int height)
{
    std::cout << sprite[0][0];
    std::cout << sprite[0][1];
    std::cout << sprite[0][2];
    std::cout << "FINE"<<std::endl;
    for (int i = y; i < y + height; i++)
    {
        std::vector<char> row = canvas[i];
        for (int j = x; j < x + width; j++)
        {
            std::vector<char>::iterator iter = row.begin() + j;

            row.insert(iter, (char)this->sprite[i - y][j - x]);
        }
        std::vector<std::vector<char>>::iterator iter = canvas.begin() + i;
        canvas.insert(iter, row);
    }
    return canvas;
}
std::vector<std::string> Sprite::getSprite()
{
    return this->sprite;
}
