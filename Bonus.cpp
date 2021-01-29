#include "Bonus.hpp"

Bonus::Bonus(int bonus, int initialX, int initialY, int width, int height):Entity(initialX, initialY, width, height)
{
    this->bonus = bonus;
}

Bonus::~Bonus(){}

int Bonus::getBonus(){return this->bonus;}