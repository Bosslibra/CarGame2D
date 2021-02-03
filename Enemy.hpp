#pragma once
#include "Entity.hpp"
#include "Sprite.hpp"
#include <vector>
class Enemy : public Entity
{
private:
    int damage = 200;
    Sprite sprite;

public:
    Enemy(int damage, int initialX, int initialY, int width, int height);
    ~Enemy();
    int getDamage();
    void move(int speed, int screenWidth, int borderWidth);
    void draw(std::vector<std::vector<char>> &canvas);
    void collideLateralWalls(int screenWidth, int borderWidth);
    bool collideBottomWall(int screenHeight, int borderWidth);
};