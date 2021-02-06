#include "Game.hpp"
#include "Input.cpp"
using namespace std;

Game::Game()
{
    //constructor is absent because by setting score and level in the start() method, when the game finishes and you reset it, it automatically reset the score and the level
}

void Game::start()
{
    this->level = 1;
    this->score = 0;
    this->gameState = GAME_ON;
    //TODO set the default canvas
    Timer gameTimer = Timer();
    Input i;

    do
    {
        int coord = i.getMovementInput();
        if (coord == TOP)
        {
        }
        else if (coord == LEFT)
        {
        }
        else if (coord == RIGHT)
        {
        }
        else if (coord == DOWN)
        {
        }
        else if (coord == TOPLEFT)
        {
        }
        else if (coord == TOPRIGHT)
        {
        }
        else if (coord == DOWNLEFT)
        {
        }
        else if (coord == DOWNRIGHT)
        {
        }
        if (i.getMenuInput() == EXIT)
        {
            this->gameState = GAME_OVER;
        }
        Sleep(17);
    } while (this->gameState != GAME_OVER);
    //TODO rendering an ending screen or something?
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
