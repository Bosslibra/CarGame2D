#include "Entity.hpp"
using namespace std;

Entity::~Entity() {}
Entity::Entity(int initialX, int initialY, int width, int height)
{
    this->x = initialX;
    this->y = initialY;
    this->width = width;
    this->height = height;
};
int Entity::getX() { return this->x; }
int Entity::getY() { return this->y; }
void Entity::setY(int y) { this->y = y; }
int Entity::getHeight() { return this->height; }
int Entity::getWidth() { return this->width; }
bool Entity::isOccupied(vector<vector<char>> canvas)
{
    for (int i = this->y-1; i < this->y + this->height + 1; i++)
    {
        for (int j = this->x; j < this->x + this->width + 1; j++)
        {
            if (canvas[i][j] != ' ')
                return true;
        }
    }
    return false;
}