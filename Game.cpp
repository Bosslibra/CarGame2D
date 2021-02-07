#include "Game.hpp"
Game::~Game() {}
Game::Game()
{

    this->initCanvas();
    //score inziale
    this->score = 1;
    this->player = new Player(this->width - 4, this->height / 2, 3, 3);
    //parametri iniziali
    this->nBonus = 1;
    this->nEnemy = 2;
    this->damage = 150;
    this->bonus = 50;
    this->speed = 120;
    this->levelUpTarget = 1000;
    this->prevLevel = 0;
    console.DrawAtStart(this->canvas);
    srand((unsigned)time(0));
}
void Game::initCanvas()
{
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
void Game::run()
{
    while (this->score > 0)
    {
        this->resetCanvas();
        //aggiorno il numero di nemici/bonus a schermo
        if (this->enemies.size() < this->nEnemy)
            this->addEnemy(this->damage);
        if (this->bonuses.size() < this->nBonus)
            this->addBonus(this->bonus);

        this->move();
        this->checkCollision();
        this->draw();

        this->score += 1;
        this->checkLevel();
        Sleep(this->speed);
    }
}

void Game::checkCollision()
{
    this->player->collideWalls(this->height, this->width);
    //collide con nemici
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
    // collide con bonus
    for (int i = 0; i < bonuses.size(); i++)
    {
        bool isColliding = this->player->collideBonus(bonuses[i]);
        if (isColliding)
        {
            this->score += bonuses[i].getBonus();
            bonuses.erase(bonuses.begin() + i);
        }
    }
}
void Game::draw()
{
    //disegno player
    this->player->draw(this->canvas);
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].draw(this->canvas);
    }

    // muovo tutti i bonus
    for (int i = 0; i < bonuses.size(); i++)
    {
        bonuses[i].draw(this->canvas);
    }

    this->console.DrawBuffer(this->canvas);
}
void Game::move()
{
    this->player->move();

    //muovo tutti i nemici
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].move(this->height, 1);
        if (enemies[i].collideBottomWall(this->width, enemies[i].getHeight()))
        {
            enemies.erase(enemies.begin() + i);
        }
    }

    // muovo tutti i bonus
    for (int i = 0; i < bonuses.size(); i++)
    {
        bonuses[i].move();
        if (bonuses[i].collideBottomWall(this->width, bonuses[i].getHeight()))
        {
            bonuses.erase(bonuses.begin() + i);
        }
    }
}
void Game::addEnemy(int damage)
{

    int yPos = rand() % (width - 3) + 3;
    Enemy e(damage, 1, yPos, 3, 3);
    // se NON è occupato allora aggiungo il nemico, altrimenti aspetto.
    if (!e.isOccupied(this->canvas))
    {
        this->enemies.push_back(e);
    }
}
void Game::addBonus(int bonus)
{
    int yPos = rand() % (width - 3) + 3;
    Bonus b(bonus, 1, yPos, 1, 1);
    // se NON è occupato allora aggiungo il nemico, altrimenti aspetto.
    if (!b.isOccupied(this->canvas))
    {
        this->bonuses.push_back(b);
    }
}

void Game::resetCanvas()
{
    this->player->remove(this->canvas);
    for (int i = 0; i < enemies.size(); i++)
    {
        this->enemies[i].remove(this->canvas);
    }
    for (int i = 0; i < bonuses.size(); i++)
    {
        this->bonuses[i].remove(this->canvas);
    }
}
void Game::checkLevel()
{
    if (this->score >= this->levelUpTarget)
    {
        this->nEnemy++;
        this->nBonus++;
        this->speed -= 5; //accellera
        this->damage += 50;
        this->bonus += 20;
        this->prevLevel = this->levelUpTarget;
        this->levelUpTarget += 1000;
    }
    else if (this->score < this->prevLevel)
    {
        this->nEnemy--;
        this->nBonus--;
        this->speed += 5; // rallenta
        this->damage -= 50;
        this->bonus -= 20;
        this->levelUpTarget = this->prevLevel;
        this->prevLevel -= 1000;
    }
}