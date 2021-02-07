#include "Game.hpp"
#include "Input.cpp"
#include "LevelInterface.cpp"
using namespace std;

Game::Game()
{
    LevelInterface board;
    this->board = board;
}

void Game::start()
{
    this->board.setup();
    Input i;
    do
    {
        // this->board.moveGame();
        int coord = i.getMovementInput();
        if (coord == INPUT_TOP)
        {
            this->board.movePlayer(INPUT_TOP);
        }
        else if (coord == INPUT_LEFT)
        {
            this->board.movePlayer(INPUT_LEFT);
        }
        else if (coord == INPUT_RIGHT)
        {
            this->board.movePlayer(INPUT_RIGHT);
        }
        else if (coord == INPUT_DOWN)
        {
            this->board.movePlayer(INPUT_DOWN);
        }
        else if (coord == INPUT_TOPLEFT)
        {
            this->board.movePlayer(INPUT_TOPLEFT);
        }
        else if (coord == INPUT_TOPRIGHT)
        {
            this->board.movePlayer(INPUT_TOPRIGHT);
        }
        else if (coord == INPUT_DOWNLEFT)
        {
            this->board.movePlayer(INPUT_DOWNLEFT);
        }
        else if (coord == INPUT_DOWNRIGHT)
        {
            this->board.movePlayer(INPUT_DOWNRIGHT);
        }
        if (i.getMenuInput() == INPUT_EXIT)
        {
            this->board.gameState = GAME_OVER;
        }
        Sleep(17);
    } while (this->board.gameState == GAME_ON);
    this->board.gameOver();
}
