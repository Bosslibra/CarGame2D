#include <Player.hpp>

Player::Player(int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
}

bool Player::collideEnemy(Enemy e)
{
    int eWidth = e.getWidth();
    int eHeight = e.getHeight();
    int eX = e.getX();
    int eY = e.getY();
    //check collisioni hitbox
    if (this->x<eX + eWidth &&this->x + this->width> eX &&
        this->y<eY + eHeight &&this->y + this->height> eY)
    {
        return true;
    }
    return false;
}
bool Player::collideBonus(Bonus b)
{
    int bWidth = b.getWidth();
    int bHeight = b.getHeight();
    int eX = b.getX();
    int eY = b.getY();
    //check collisioni hitbox
    if (this->x<eX + bWidth &&this->x + this->width> eX &&
        this->y<eY + bHeight &&this->y + this->height> eY)
    {
        return true;
    }
    return false;
}