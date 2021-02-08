#pragma once
#include <vector>
using namespace std;
#include "ConsoleDrawing.hpp"
#include "Sprite.hpp"

#define GAME_ON 0
#define GAME_OVER 1
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
    static int bonusLimit;
    static int enemyLimit;
    static int mineLimit;
    static int internal_score;
    static int bottom_wall_id;
    static vector<Sprite> Enemies;
    static vector<Sprite> Bonuses;
    static vector<Sprite> Mines;
    int score;
    int level;
    ConsoleDrawing canvas_handler;
    void addScore(int score);
    void removeScore(int score);
    void removeEnemy(int spriteID);
    void removeBonus(int spriteID);
    void removeMine(int spriteID);
    void recursive_movement(int last_direction, int id);

public:
    LevelInterface();
    void movePlayer(int direction);
    void moveGame();
    void setup();
    void gameOver();
    void spawner();
    int gameState; //0 active, 1 gameOver
};
