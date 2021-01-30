#pragma once
#include "Entity.hpp"
#include "Sprite.hpp"
class Enemy : public Entity
{
private:
    int damage = 200;
    Sprite sprite;
public:
    Enemy(int damage, int initialX, int initialY, int width, int height);
    ~Enemy();
    int getDamage();
};
