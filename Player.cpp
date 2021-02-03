#include "Player.hpp"
Player::~Player() {}
Player::Player(int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
	// crea lo sprite collegato al player
	std::string one = "O*O";
	std::string two = "*A*";
	std::string three = "O*O";
	this->sprite.addLine(one);
	this->sprite.addLine(two);
	this->sprite.addLine(three);
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
bool Player::collideWalls(int xMax, int yMax)
{
	//check collisioni hitbox
	if (this->x <= 0 || this->x >= xMax || this->y <= 0 || this->y >= yMax)
	{
		return true;
	}
	return false;
}
Sprite Player::getSprite()
{
	return this->sprite;
}
void Player::move(int direction, int speed)
{
	switch (direction)
	{
	case TOP:
		this->x -= speed;
		break;
	case TOPLEFT:
		this->y -= speed / 2;
		this->x -= speed / 2;
		break;
	case TOPRIGHT:
		this->y -= speed / 2;
		this->x += speed / 2;
		break;
	case RIGHT:
		this->x += speed;
		break;
	case DOWNLEFT:
		this->y += speed / 2;
		this->x -= speed / 2;
		break;
	case DOWNRIGHT:
		this->y += speed / 2;
		this->x += speed / 2;
		break;
	case DOWN:
		this->y += speed;
		break;
	case LEFT:
		this->x -= speed;
		break;
	default:
		break;
	}
}
void Player::draw(std::vector<std::vector<char>> &canvas)
{
	this->sprite.draw(canvas, this->x, this->y, this->width, this->height);
}