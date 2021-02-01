#include "Bonus.hpp"

Bonus::Bonus(int bonus, int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
    this->bonus = bonus;
}

Bonus::~Bonus() {}

int Bonus::getBonus() { return this->bonus; }
void Bonus::move(int speed)
{
    this->y += speed;
}
void Bonus::draw(std::vector<std::vector<char>> &canvas)
{
	this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}