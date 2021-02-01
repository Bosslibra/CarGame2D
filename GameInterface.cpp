#include "GameInterface.hpp"
#include <random>
#include <ctime>
#include <iostream>
GameInterface::GameInterface()
{
    //score inziale
    this->score = 1;
    this->player = new Player(this->width / 2, this->height - 3, 3, 3);
    //numero entità iniziali
    this->nBonus = 1;
    this->nEnemy = 1;
    this->damage = 100;
    this->bonus = 50;
    this->speed = 1;
    this->levelUpTaret = 1000;
}
void GameInterface::run()
{
    // resetto canvas
    this->resetCanvas();
    if (this->enemies.size() < this->nEnemy)
        this->addEnemy(this->damage);
    if (this->bonuses.size() < this->nBonus)
        this->addBonus(this->bonus);
    this->move(1);
    this->draw();
    this->checkCollision();
    this->score += 1;
    this->checkLevel()
}

void GameInterface::checkCollision()
{
   std::list<Enemy>::iterator enemyIt;
    for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
    {
        bool isColliding = this->player->collideEnemy(*enemyIt);
        if (isColliding){
            this->score -= enemyIt->getDamage();
            enemies.remove(*enemyIt);
        }
    }
    // muovo tutti i bonus
    std::list<Bonus>::iterator bonusIt;
    for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
    {
        bool isColliding = this->player->collideBonus(*bonusIt);
        if (isColliding){
            this->score += bonusIt->getBonus();
            bonuses.remove(*bonusIt);
        }
    }
}
void GameInterface::draw()
{
    //disegno player
    this->player->draw(this->canvas);

    std::list<Enemy>::iterator enemyIt;
    for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
    {
        enemyIt->draw(this->canvas);
    }
    // muovo tutti i bonus
    std::list<Bonus>::iterator bonusIt;
    for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
    {
        bonusIt->draw(this->canvas);
    }
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            std::cout<<canvas[i][j];
        }
        std::cout<<std::endl;
    }
}
void GameInterface::move(int direction)
{
    this->player->move(direction, speed);
    //muovo tutti i nemici
    std::list<Enemy>::iterator enemyIt;
    for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
    {
        enemyIt->move(this->speed);
    }
    // muovo tutti i bonus
    std::list<Bonus>::iterator bonusIt;
    for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
    {
        bonusIt->move(this->speed);
    }
}
void GameInterface::addEnemy(int damage)
{
    srand((unsigned)time(0));
    int xPos = rand() % width + 3;
    Enemy e(damage, xPos, 3, 3, 3);
    this->enemies.push_back(e);
}
void GameInterface::addBonus(int bonus)
{
    srand((unsigned)time(0));
    int xPos = rand() % width + 3;
    Bonus b(bonus, xPos, 3, 1, 1);
    this->bonuses.push_back(b);
}
void GameInterface::setScore(int score)
{
    this->score += score;
}
void GameInterface::resetCanvas()
{
    for (int i = 0; i < this->height; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < this->width; j++)
        {
            row.push_back(' ');
        }
        this->canvas.push_back(row);
    }
}
void GameInterface::checkLevel(){
    if (this->score >= this->levelUpTaret){
        this->levelUpTaret += 1000;
        this->nEnemy++;
        this->nBonus++;
        this->speed += 1;
    }
}