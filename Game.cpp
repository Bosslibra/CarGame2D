#include "Game.hpp"
#include "timercpp.h"
using namespace std;

Game::Game()
{
    //constructor is absent because by setting score and level in the start() method, when the game finishes and you reset it, it automatically reset the score and the level
}

void Game::start()
{
    this->level = 1;
    this->score = 0;
    //TODO set the default canvas
    Timer gameTimer = Timer();
    gameTimer.setInterval([&]() {
        this->changeState(gameTimer);
    },
                          16); //every 1/60th of a second
}

void Game::changeState(Timer gameTimer)
{
    if (this->gameState != GAME_OVER)
    {
        //TODO this is the center of the game, here we'll move sprites and stuff
    }
    else
    {
        gameTimer.stop();
        //TODO rendering an ending screen or something?
    }
}

void Game::addScore(int score)
{
    if (this->internal_score + score > 1000)
    {
        this->level++;
        this->internal_score = 0;
    }
    this->score += score;
    this->internal_score += score;
}

void Game::removeScore(int score)
{
    if (this->score - score <= 0)
    {
        this->gameState = GAME_OVER;
    }
    else
    {
        this->score -= score;
        this->internal_score -= score;
    }
}
