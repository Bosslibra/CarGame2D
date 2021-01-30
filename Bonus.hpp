#pragma once
#include "Entity.hpp"
class Bonus : public Entity
{
private:
    int bonus = 100; //default
public:
    Bonus(int bonus,int initialX, int initialY, int width, int height);
    ~Bonus();
    int getBonus();
};


