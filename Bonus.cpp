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
bool Bonus::collideBottomWall(int screenHeight, int borderWidth){
    borderWidth -= 1; //per avere la coordinata dell'ultimo punto del bordo
    if (this->x >= screenHeight - borderWidth){
        return true;
    }
    return false;
}