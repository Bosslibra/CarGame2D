#include <Player.hpp>

Player::Player(int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
}

/*collisioni tra player e un'altra entità qualsiasi
 *@param Entity entità con cui si scontra (Enemy o Bonus)
 */
bool Player::collide(Entity e)
{
    int eWitdth = e.getWidth();
    int eHeight = e.getHeight();
    int eX = e.getX();
    int eY = e.getY();
    //check collisioni hitbox
    if (this->x<eX + eWitdth &&this->x + this->width> eX &&
        this->y<eY + eHeight &&this->y + this->height> eY)
    {
        return true;
    }
    return false;
}