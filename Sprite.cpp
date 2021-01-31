#include "Sprite.hpp"
#include <list>
#include <string>
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

void Sprite::draw(char *canvas, int x, int y, int width, int height)
{
    for (int i = y; i < height; i++)
    {
        for (int j = x; j < width; j++)
        {
            canvas[i][j] = '*';
        }
    }
}
std::list<std::string> Sprite::getSprite()
{
    return this->sprite;
}
