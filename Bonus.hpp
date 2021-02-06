#pragma once
#include "Entity.hpp"
#include "Sprite.hpp"
#include "Enemy.hpp"
#include <vector>
#include <list>
class Bonus : public Entity
{
private:
    int bonus;
    Sprite sprite;
public:
    Bonus(int bonus,int initialX, int initialY, int width, int height);
    ~Bonus();
    int getBonus();
    void move(int speed);
    void draw(std::vector<std::vector<char>> &canvas);
    bool collideBottomWall(int screenHeight, int borderWidth);
//     void collideBonus(std::list<Bonus> bonuses);
//     void collideEnemy(std::list<Enemy> enemies);
};


