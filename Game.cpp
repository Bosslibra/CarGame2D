#include "Game.hpp"
using namespace std;
Game::~Game() {}
Game::Game()
{
    srand((unsigned)time(0));
    this->initGame();

}
void Game::initGame()
{

    //score e level inziali
    this->score = 1;
    this->level = 1;
    this->player = new Player(this->height - 4, this->width / 2, 3, 3);
    //parametri iniziali
    this->nBonus = 1;
    this->nEnemy = 2;
    this->damage = 150;
    this->bonus = 50;
    this->speed = 120;
    this->levelUpTarget = 1000;
    this->prevLevel = 0;

    for (int i = 0; i < this->width; i++)
    {
        vector<char> row;
        for (int j = 0; j < this->height; j++)
        {
            if (j == 0 || j == this->height - 1 || i == this->width - 1 || i == 0)
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
    console.DrawAtStart(this->showStats());
}
void Game::run()
{
    bool restart = true;
    do
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
        this->score =1;
        restart = this->gameOver();
    }while(restart);
}

void Game::checkCollision()
{
    this->player->collideWalls(this->width, this->height);
    //collide con nemici
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool isColliding = this->player->collideEnemy(this->enemies[i]);
        if (isColliding)
        {
            this->score -= this->enemies[i].getDamage();
            this->enemies.erase(this->enemies.begin() + i);
        }
        else
        {
            Enemy e = this->enemies[i];
            this->enemies.erase(this->enemies.begin() + i);
            e.collideBonus(this->bonuses);
            e.collideEnemy(this->enemies);
            this->enemies.push_back(e);
        }
    }
    // collide con bonus
    for (int i = 0; i < bonuses.size(); i++)
    {
        bool isColliding = this->player->collideBonus(this->bonuses[i]);
        if (isColliding)
        {
            this->score += this->bonuses[i].getBonus();
            this->bonuses.erase(this->bonuses.begin() + i);
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
    //quando disegna ha già il canvas compreso dello score e level
    this->console.DrawBuffer(this->showStats());
}
void Game::move()
{
    this->player->move();

    //muovo tutti i nemici
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].move(this->width, 1);
        if (enemies[i].collideBottomWall(this->height, enemies[i].getHeight()))
        {
            enemies.erase(enemies.begin() + i);
        }
    }

    // muovo tutti i bonus
    for (int i = 0; i < bonuses.size(); i++)
    {
        bonuses[i].move();
        if (bonuses[i].collideBottomWall(this->height, bonuses[i].getHeight()))
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
        this->level++;
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
        this->level--;
        this->nEnemy--;
        this->nBonus--;
        this->speed += 5; // rallenta
        this->damage -= 50;
        this->bonus -= 20;
        this->levelUpTarget = this->prevLevel;
        this->prevLevel -= 1000;
    }
}
vector<vector<char>> Game::showStats()
{
    LevelInterface l;
    l.setHeight(this->height);
    l.drawCanva(this->level, this->score);
    vector<vector<char>> statsCanvas = l.getCanvas();
    vector<vector<char>> result;
    result.reserve(this->canvas.size() + statsCanvas.size());
    result.insert(result.end(), this->canvas.begin(), this->canvas.end());
    result.insert(result.end(), statsCanvas.begin(), statsCanvas.end());

    return result;
}
bool Game::gameOver()
{
    vector<string> gameOver;

    //salvo come stringhe le righe che compongono la scritta "game Over"
    gameOver.push_back("  __ _  __ _ _ __ ___   ___    _____   _____ _ __  ");
    gameOver.push_back(" / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|");
    gameOver.push_back("| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   ");
    gameOver.push_back(" \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   ");
    gameOver.push_back("  __/ |                                           ");
    gameOver.push_back(" |___/                                            ");

    vector<vector<char>> canvas;
    //scrivo la scritta gameover
    for (int i = 0; i < gameOver.size(); i++)
    {
        vector<char> row;
        for (int j = 0; j < gameOver[i].length(); j++)
        {
            row.push_back(gameOver[i].at(j));
        }
        canvas.push_back(row);
    }
    this->console.drawGameOver(canvas);
    // se il giocatore preme invio il gioco continua altrimenti si ferma
    Sleep(200);
    Input i;
    bool continueCondition;

    if (i.getMenuInput() == ENTER){
        continueCondition = true;
        this->canvas.clear();
        this->initGame();
    } else {
        continueCondition = false;
    }
    return continueCondition;
}
