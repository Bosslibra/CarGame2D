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

std::vector <std::vector <char>> Sprite::draw(std::vector<std::vector<char>> canvas, int x, int y, int width, int height)
{
    for (int i = y; i < height; i++)
    {
        std::vector<char> row = canvas[i];
        for (int j = x; j < width; j++)
        {
            std::vector<char>::iterator iter = row.begin() + j;
            row.insert(iter, '*');

        }
        std::cout<<"CULO"<<std::endl;
        std::cout<<x;
        for(char item:row){
            std::cout<<item;
        }
        std::vector<std::vector<char>>::iterator iter = canvas.begin() + i;
        canvas.insert(iter, row);
    }
    return canvas;
}
std::list<std::string> Sprite::getSprite()
{
    return this->sprite;
}
