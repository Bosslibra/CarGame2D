#include "Sprite.hpp"
#include "Bonus.hpp"
#include <ctime>
#include <vector>

#define DIR_LEFT 0
#define DIR_RIGHT 1
class Enemy : public Entity
{
private:
    int damage = 200;
    int yDirection;
    Sprite sprite;

public:
    Enemy(int damage, int initialX, int initialY, int width, int height);
    ~Enemy();
    int getDamage();
    void move(int screenWidth, int borderWidth);
    void draw(std::vector<std::vector<char>> &canvas);
    void remove(std::vector<std::vector <char>> &canvas);
    void collideLateralWalls(int screenWidth, int borderWidth);
    bool collideBottomWall(int screenHeight, int borderWidth);
    void collideBonus(std::vector<Bonus> bonuses);
    void collideEnemy(std::vector<Enemy> enemies);
};