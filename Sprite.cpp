#include "Sprite.hpp"

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

void Sprite::draw(std::vector<std::vector<char>> &canvas, int x, int y, int width, int height)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {

            canvas[i][j] =this->sprite[i - y][j - x];
        }
    }
}
void Sprite::remove(std::vector<std::vector<char>> &canvas, int x, int y, int width, int height)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {

            canvas[i][j] =' ';
        }
    }
}
std::vector<std::string> Sprite::getSprite()
{
    return this->sprite;
}
