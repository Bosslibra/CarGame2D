#pragma once
#include <vector>
using namespace std;
#include "ConsoleDrawing.hpp"
#include "Sprite.hpp"

#define CANVAS_HEIGHT 40
#define CANVAS_WIDTH 80
#define PLAYER_WIDTH (CANVAS_WIDTH / 4) * 3
#define SCORE_HEIGHT (CANVAS_HEIGHT / 4)
#define PLAYER_STARTING_X (PLAYER_WIDTH) / 2

class LevelInterface
{
private:
    static Sprite player;
    static int enemySpeed;
    static vector<Sprite> Enemies;
    static vector<Sprite> Bonuses;
    ConsoleDrawing canvas_handler;

public:
    LevelInterface();
    void movePlayer(int direction);
    void moveGame();
    void setup();
    void increaseEnemies();
    void decreaseEnemies();
    void increaseBonuses();
    void decreaseBonuses();
    void updateScore(int score);
    void updateLevel(int level);
};
