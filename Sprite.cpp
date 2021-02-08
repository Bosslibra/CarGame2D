#include "Sprite.hpp"
using namespace std;
Sprite::Sprite()
{
}
Sprite::~Sprite()
{
}
void Sprite::addLine(string line)
{
    this->sprite.push_back(line);
}

void Sprite::draw(vector<vector<char>> &canvas, int x, int y, int width, int height)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {

            canvas[i][j] = this->sprite[i - y][j - x];
        }
    }
}
void Sprite::remove(vector<vector<char>> &canvas, int x, int y, int width, int height)
{
    for (int i = y; i < y + height; i++)
    {
        for (int j = x; j < x + width; j++)
        {

            canvas[i][j] = ' ';
        }
    }
}
vector<string> Sprite::getSprite()
{
    return this->sprite;
}
