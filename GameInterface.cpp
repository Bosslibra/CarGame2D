#include "GameInterface.hpp"
#include <random>
#include <ctime>
#include <iostream>
#include <windows.h>
GameInterface::GameInterface()
{
    this->resetCanvas();
    //score inziale
    this->score = 1;
    this->player = new Player(this->width - 3, this->height / 2, 3, 3);
    //numero entità iniziali
    this->nBonus = 1;
    this->nEnemy = 1;
    this->damage = 100;
    this->bonus = 50;
    this->speed = 1;
    this->levelUpTarget = 1000;
    console.DrawAtStart(this->canvas);
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
    this->checkCollision();
    this->draw();
    // this->score += 1;
    // this->checkLevel();

    // for (int i = 0; i < this->height; i++)
    // {
    //     for (int j = 0; j < this->width; j++)
    //     {
    //         std::cout<<this->canvas[i][j];
    //     }
    //     std::cout<<std::endl;
    // }
    //     std::cout<<std::endl;

    Sleep(300);
}

void GameInterface::checkCollision()
{
    if (enemies.size() > 0)
    {
        std::list<Enemy>::iterator enemyIt;
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            bool isColliding = this->player->collideEnemy(*enemyIt);
            if (isColliding)
            {
                this->score -= enemyIt->getDamage();
                enemies.erase(enemyIt);
            }
            // else
            // {
            //     enemyIt->collideBonus(this->bonuses);
            //     enemyIt->collideEnemy(this->enemies);
            // }
        }
    }

    // muovo tutti i bonus
    if (enemies.size() > 0)
    {
        std::list<Bonus>::iterator bonusIt;
        for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
        {
            bool isColliding = this->player->collideBonus(*bonusIt);
            if (isColliding)
            {
                this->score += bonusIt->getBonus();
                bonuses.erase(bonusIt);
            }
            // else
            // {
            //     bonusIt->collideBonus(this->bonuses);
            //     bonusIt->collideEnemy(this->enemies);
            // }
        }
    }
}
void GameInterface::draw()
{
    //disegno player
    this->player->draw(this->canvas);

    if (enemies.size() > 0)
    {
        std::list<Enemy>::iterator enemyIt;

        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            enemyIt->draw(this->canvas);
        }
    }
    // muovo tutti i bonus
    if (bonuses.size() > 0)
    {
        std::list<Bonus>::iterator bonusIt;

        for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
        {
            bonusIt->draw(this->canvas);
        }
    }

    this->console.DrawBuffer(this->canvas);
}
void GameInterface::move(int direction)
{
    this->player->move(direction, speed);
    //muovo tutti i nemici
    if (enemies.size() > 0)
    {
        std::list<Enemy>::iterator enemyIt;
        for (enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt)
        {
            enemyIt->move(this->speed, this->height, 1);
            if (enemyIt->collideBottomWall(this->width, 1))
            {
                enemies.erase(enemyIt);
            }
        }
    }

    // muovo tutti i bonus
    if (bonuses.size() > 0)
    {
        std::list<Bonus>::iterator bonusIt;
        for (bonusIt = bonuses.begin(); bonusIt != bonuses.end(); ++bonusIt)
        {
            bonusIt->move(this->speed);
        }
    }
}
void GameInterface::addEnemy(int damage)
{
    srand((unsigned)time(0));
    int yPos = rand() % (width - 3) + 3;
    Enemy e(damage, 3, yPos, 3, 3);
    this->enemies.push_back(e);
}
void GameInterface::addBonus(int bonus)
{
    srand((unsigned)time(0));
    int yPos = rand() % (width - 3) + 3;
    Bonus b(bonus, 3, yPos, 1, 1);
    this->bonuses.push_back(b);
}
void GameInterface::setScore(int score)
{
    this->score += score;
}
void GameInterface::resetCanvas()
{
    this->canvas.clear();
    for (int i = 0; i < this->height; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < this->width; j++)
        {
            if (j == 0 || j == this->width - 1 || i == this->height - 1 || i == 0)
            {
                row.push_back('#');
            }
            else
            {
                row.push_back(' ');
            }
        }
        this->canvas.push_back(row);
    }
}
// void GameInterface::checkLevel()
// {
//     if (this->score >= this->levelUpTarget)
//     {
//         this->levelUpTarget += 1000;
//         this->nEnemy++;
//         this->nBonus++;
//         this->speed += 1;
//     }
// }