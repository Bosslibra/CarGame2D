#pragma once
#include "LevelInterface.hpp"
using namespace std;
class Game
{
private:
    LevelInterface board; //level handler

public:
    Game();
    void start();
};
