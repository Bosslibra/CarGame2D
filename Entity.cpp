#include <Entity.hpp>

Entity::Entity(int initialX, int initialY, int width, int height)
{
    this->x = initialX;
    this->y = initialY;
    this->width = width;
    this->height = height;
};
int Entity::getX(){return this->x;}
int Entity::getY(){return this->y;}
int Entity::getHeight() { return this->height; }
int Entity::getWidth() { return this->width; }