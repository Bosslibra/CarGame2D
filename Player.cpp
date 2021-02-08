#include "Player.hpp"
using namespace std;
Player::~Player() {}
Player::Player(int initialX, int initialY, int width, int height) : Entity(initialX, initialY, width, height)
{
	// crea lo sprite collegato al player
	string one = "O|O";
	string two = "^A-";
	string three = "O|O";
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
void Player::collideWalls(int width, int height)
{
	//check collisioni hitbox
	if (this->x <= 0)
	{
		this->x = 1;
	}
	if (this->x + this->height >= height)
	{
		this->x = height - this->height - 1;
	}
	if (this->y <= 0)
	{
		this->y = 1;
	}
	if (this->y + this->width >= width)
	{
		this->y = width - this->width - 1;
	}
}
Sprite Player::getSprite()
{
	return this->sprite;
}
void Player::move()
{
	int speed = 2;
	Input i;
	int direction = i.getMovementInput();
	switch (direction)
	{
	case TOP:
		this->x -= speed;
		break;
	case TOPLEFT:
		this->y -= speed;
		this->x -= speed;
		break;
	case TOPRIGHT:
		this->x -= speed;
		this->y += speed;
		break;
	case RIGHT:
		this->y += speed;
		break;
	case DOWNLEFT:
		this->x += speed;
		this->y -= speed;
		break;
	case DOWNRIGHT:
		this->y += speed;
		this->x += speed;
		break;
	case DOWN:
		this->x += speed;
		break;
	case LEFT:
		this->y -= speed;
		break;
	default:
		break;
	}
}
void Player::draw(vector<vector<char>> &canvas)
{
	this->sprite.draw(canvas, this->x, this->y, this->height, this->width);
}
void Player::remove(vector<vector<char>> &canvas)
{
	this->sprite.remove(canvas, this->x, this->y, this->height, this->width);
}