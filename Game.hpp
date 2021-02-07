#pragma once
#include <vector>
#include <string>
#include "LevelInterface.hpp"
#define GAME_ON 0
#define GAME_OVER 1
using namespace std;
class Game
{
private:
    LevelInterface board;          //level handler
    int gameState;                 //0 active, 1 gameOver
    int level;                     //current level
    int score;                     //current score
    int internal_score;            //score that resets to 0 every time the normal score reaches the next thousand unit
    vector<vector<string>> canvas; //graphic container
    int setLevel(int level);
    int getLevel(int level);
    void addScore(int score);
    void removeScore(int score);

public:
    Game();
    void start();
    vector<vector<string>> getCanvas();
    void setCanvas(vector<vector<string>> canvas);
};
