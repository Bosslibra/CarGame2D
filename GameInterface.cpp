#include "GameInterface.hpp"

GameInterface::GameInterface()
{
    this->resetCanvas();
    //score inziale
    this->score = 1;
    this->player = new Player(this->width - 3, this->height / 2, 3, 3);
    //numero entità iniziali
    this->nBonus = 1;
    this->nEnemy = 2;
    this->damage = 100;
    this->bonus = 50;
    this->speed = 1;
    this->levelUpTarget = 1000;
    console.DrawAtStart(this->canvas);
    srand((unsigned)time(0));
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
        for (int i = 0; i < enemies.size(); i++)
        {
            bool isColliding = this->player->collideEnemy(enemies[i]);
            if (isColliding)
            {
                this->score -= enemies[i].getDamage();
                enemies.erase(enemies.begin() + i);
            }
            else
            {
                enemies[i].collideBonus(this->bonuses);
                enemies[i].collideEnemy(this->enemies);
            }
        }
    }

    // muovo tutti i bonus
    if (bonuses.size() > 0)
    {
        for (int i = 0; i < bonuses.size(); i++)
        {
            bool isColliding = this->player->collideBonus(bonuses[i]);
            if (isColliding)
            {
                this->score += bonuses[i].getBonus();
                bonuses.erase(bonuses.begin() + i);
            }
            // else
            // {
            //     bonuses[i].collideBonus(this->bonuses);
            //     bonuses[i].collideEnemy(this->enemies);
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
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].draw(this->canvas);
        }
    }
    // muovo tutti i bonus
    if (bonuses.size() > 0)
    {

        for (int i = 0; i < bonuses.size(); i++)
        {
            bonuses[i].draw(this->canvas);
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
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i].move(this->speed, this->height, 1);
            if (enemies[i].collideBottomWall(this->width, 1))
            {
                enemies.erase(enemies.begin() + i);
            }
        }
    }

    // muovo tutti i bonus
    if (bonuses.size() > 0)
    {
        for (int i = 0; i < bonuses.size(); i++)
        {
            bonuses[i].move(this->speed);
            if (bonuses[i].collideBottomWall(this->width, 1))
            {
                bonuses.erase(bonuses.begin() + i);
            }
        }
    }
}
void GameInterface::addEnemy(int damage)
{
    int yPos = rand() % (width - 3) + 3;
    Enemy e(damage, 3, yPos, 3, 3);
    this->enemies.push_back(e);
}
void GameInterface::addBonus(int bonus)
{
    int yPos = rand() % (width - 3) + 3;
    Bonus b(bonus, 3, yPos, 1, 1);
    // if(!b.collideEnemy(this->enemies))
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