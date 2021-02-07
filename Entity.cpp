#include "Entity.hpp"

Entity::~Entity(){}
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
bool Entity::isOccupied(std::vector<std::vector<char>> canvas){
    for(int i = this->y; i< this->y+this->height; i++){
        for (int j = this->x; j < this->x+this->width; j++)
        {
            if(canvas[i][j] != ' ')
                return true;
        }
    }
    return false;
}