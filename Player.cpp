#include <windows.h>

#include <Player.hpp>

Player::Player(int startX, int startY, int width, int height)
    : Entity(startX, startY, width, height) {
    x = startX;
    y = startY;
    width = width;
    height = height;
}

int Player::getX() { return x; }
int Player::getY() { return y; }
int getWidth() { return width; }
int getHeight() { return height; }
bool Player::collide(Entity e) {
    int eWidth = e.getWidth();
    int eHeight = e.getHeight();
    int eX = e.getX();
    int eY = e.getY();

    // magia
    if (x < eX + eWidth && x + width > eX && y < eY + eHeight &&
        y + height > eY) {
        // collision detected
        return true;
    } else {
        return false;
    }
}
void move(int speed) {}