#include "LevelInterface.hpp"
#include "ConsoleDrawing.cpp"
#include "Sprite.cpp"
using namespace std;
Sprite LevelInterface::player;
int LevelInterface::enemySpeed;
int LevelInterface::bonusLimit;
int LevelInterface::enemyLimit;

LevelInterface::LevelInterface()
{
    ConsoleDrawing c;
    this->canvas_handler = c;
}

void LevelInterface::setup()
{
    //hardwriting is a lot faster than cycling through the whole canvas

    //setting the canvas
    vector<vector<char>> canvas(CANVAS_WIDTH, vector<char>(CANVAS_HEIGHT));
    Sprite::setCanvas(canvas);

    // hardwriting the walls,score and level
    vector<vector<int>> wall_position;
    wall_position.push_back({PLAYER_WIDTH + 2, SCORE_HEIGHT, (int)'S'});
    wall_position.push_back({PLAYER_WIDTH + 3, SCORE_HEIGHT, (int)'C'});
    wall_position.push_back({PLAYER_WIDTH + 4, SCORE_HEIGHT, (int)'O'});
    wall_position.push_back({PLAYER_WIDTH + 5, SCORE_HEIGHT, (int)'R'});
    wall_position.push_back({PLAYER_WIDTH + 6, SCORE_HEIGHT, (int)'E'});
    wall_position.push_back({PLAYER_WIDTH + 7, SCORE_HEIGHT, (int)':'});
    wall_position.push_back({PLAYER_WIDTH + 8, SCORE_HEIGHT, (int)' '});
    wall_position.push_back({PLAYER_WIDTH + 9, SCORE_HEIGHT, (int)'0'});
    wall_position.push_back({PLAYER_WIDTH + 2, SCORE_HEIGHT + 1, (int)'L'});
    wall_position.push_back({PLAYER_WIDTH + 3, SCORE_HEIGHT + 1, (int)'E'});
    wall_position.push_back({PLAYER_WIDTH + 4, SCORE_HEIGHT + 1, (int)'V'});
    wall_position.push_back({PLAYER_WIDTH + 5, SCORE_HEIGHT + 1, (int)'E'});
    wall_position.push_back({PLAYER_WIDTH + 6, SCORE_HEIGHT + 1, (int)'L'});
    wall_position.push_back({PLAYER_WIDTH + 7, SCORE_HEIGHT + 1, (int)':'});
    wall_position.push_back({PLAYER_WIDTH + 8, SCORE_HEIGHT + 1, (int)' '});
    wall_position.push_back({PLAYER_WIDTH + 9, SCORE_HEIGHT + 1, (int)'1'});

    for (int y = 0; y < CANVAS_HEIGHT; y++)
    {
        wall_position.push_back({0, y, (int)'|'});
        wall_position.push_back({CANVAS_WIDTH - 1, y, (int)'|'});
        // canvas.at(0).at(y) = '|';
        // canvas.at(CANVAS_WIDTH - 1).at(y) = '|';
        if (y != 0 && y != CANVAS_HEIGHT)
        {
            // canvas.at(1).at(y) = '#';
            // canvas.at(PLAYER_WIDTH).at(y) = '#';
            wall_position.push_back({1, y, (int)'#'});
            wall_position.push_back({PLAYER_WIDTH, y, (int)'#'});
        }
    }
    for (int x = 0; x < CANVAS_WIDTH; x++)
    {
        // canvas.at(x).at(0) = '-';
        // canvas.at(x).at(CANVAS_HEIGHT - 1) = '-';
        wall_position.push_back({x, 0, (int)'-'});
        wall_position.push_back({x, CANVAS_HEIGHT - 1, (int)'-'});
    }

    //hardwriting the player
    vector<vector<int>> player_position;
    vector<int> ppoint1 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 3, (int)'*'};
    vector<int> ppoint2 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 4, (int)'P'};
    vector<int> ppoint3 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 5, (int)'*'};
    vector<int> ppoint4 = {PLAYER_STARTING_X + 1, CANVAS_HEIGHT - 4, (int)'*'};
    vector<int> ppoint5 = {PLAYER_STARTING_X - 1, CANVAS_HEIGHT - 4, (int)'*'};
    player_position.push_back(ppoint1);
    player_position.push_back(ppoint2);
    player_position.push_back(ppoint3);
    player_position.push_back(ppoint4);
    player_position.push_back(ppoint5);

    //hardwiring two enemies
    vector<vector<int>> ep1;
    vector<int> e1point1 = {15, 1, (int)'*'};
    vector<int> e1point2 = {15, 2, (int)'E'};
    vector<int> e1point3 = {15, 3, (int)'*'};
    vector<int> e1point4 = {15 + 1, 2, (int)'*'};
    vector<int> e1point5 = {15 - 1, 2, (int)'*'};
    ep1.push_back(e1point1);
    ep1.push_back(e1point2);
    ep1.push_back(e1point3);
    ep1.push_back(e1point4);
    ep1.push_back(e1point5);

    vector<vector<int>> ep2;
    vector<int> e2point1 = {45, 1, (int)'*'};
    vector<int> e2point2 = {45, 2, (int)'E'};
    vector<int> e2point3 = {45, 3, (int)'*'};
    vector<int> e2point4 = {45 + 1, 2, (int)'*'};
    vector<int> e2point5 = {45 - 1, 2, (int)'*'};
    ep2.push_back(e2point1);
    ep2.push_back(e2point2);
    ep2.push_back(e2point3);
    ep2.push_back(e2point4);
    ep2.push_back(e2point5);

    //loading sprites
    Sprite player(player_position, PLAYER);
    Sprite wall(wall_position, WALL);
    Sprite enemy1(ep1, ENEMY);
    Sprite enemy2(ep2, ENEMY);
    player.load();
    wall.load();
    enemy1.load();
    enemy2.load();
    LevelInterface::player = player;
    LevelInterface::Enemies.push_back(enemy1);
    LevelInterface::Enemies.push_back(enemy2);
    this->canvas_handler.DrawAtStart(Sprite::getCanvas());
}

void LevelInterface::moveGame()
{
    int direction;
    int after_move;
    switch (direction)
    {
    case INPUT_TOP:
        after_move = LevelInterface::player.move(UP, 0, -1);
        break;
    case INPUT_LEFT:
        after_move = LevelInterface::player.move(LEFT, -1, 0);
        break;
    case INPUT_RIGHT:
        after_move = LevelInterface::player.move(RIGHT, 1, 0);
        break;
    case INPUT_DOWN:
        after_move = LevelInterface::player.move(DOWN, 0, 1);
        break;
    case INPUT_TOPLEFT:
        after_move = LevelInterface::player.move(UP_LEFT, -1, -1);
        break;
    case INPUT_TOPRIGHT:
        after_move = LevelInterface::player.move(UP_RIGHT, 1, -1);
        break;
    case INPUT_DOWNLEFT:
        after_move = LevelInterface::player.move(DOWN_LEFT, -1, 1);
        break;
    case INPUT_DOWNRIGHT:
        after_move = LevelInterface::player.move(DOWN_RIGHT, 1, 1);
        break;
    }
    switch (after_move)
    {
    case UPDATE_SCORE_ENEMY:
        this->removeScore(100);
        break;
    case UPDATE_SCORE_BONUS:
        this->addScore(100);
        break;
    case BOUNCE_ENEMY:
        break;
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
}

void LevelInterface::movePlayer(int direction)
{
    int after_move;
    switch (direction)
    {
    case INPUT_TOP:
        after_move = LevelInterface::player.move(UP, 0, -1);
        break;
    case INPUT_LEFT:
        after_move = LevelInterface::player.move(LEFT, -1, 0);
        break;
    case INPUT_RIGHT:
        after_move = LevelInterface::player.move(RIGHT, 1, 0);
        break;
    case INPUT_DOWN:
        after_move = LevelInterface::player.move(DOWN, 0, 1);
        break;
    case INPUT_TOPLEFT:
        after_move = LevelInterface::player.move(UP_LEFT, -1, -1);
        break;
    case INPUT_TOPRIGHT:
        after_move = LevelInterface::player.move(UP_RIGHT, 1, -1);
        break;
    case INPUT_DOWNLEFT:
        after_move = LevelInterface::player.move(DOWN_LEFT, -1, 1);
        break;
    case INPUT_DOWNRIGHT:
        after_move = LevelInterface::player.move(DOWN_RIGHT, 1, 1);
        break;
    }
    switch (after_move)
    {
    case UPDATE_SCORE_ENEMY:
        this->removeScore(100);
        break;

    case UPDATE_SCORE_BONUS:
        this->addScore(100);
        break;
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
}

void LevelInterface::addScore(int score)
{
    //TODO render new score
    if (this->internal_score + score > 1000)
    {
        this->level++;
        this->internal_score = internal_score + score - 1000;
        this->increaseEnemies();
        this->decreaseBonuses();
    }
    else
    {
        this->internal_score += score;
    }
    this->score += score;
}

void LevelInterface::removeScore(int score)
{
    //TODO render new score
    if (this->score - score <= 0)
    {
        this->gameState = GAME_OVER;
    }
    if (this->internal_score - score < 0)
    {
        this->internal_score = 1000 - internal_score + score;
        this->level--;
        this->decreaseEnemies();
        this->increaseBonuses();
    }
    else
    {
        this->internal_score -= score;
    }
    this->score -= score;
}

void LevelInterface::increaseEnemies(

){};
void LevelInterface::decreaseEnemies(

){};
void LevelInterface::increaseBonuses(

){};
void LevelInterface::decreaseBonuses(

){};

void LevelInterface::gameOver()
{
    //TODO render gameover screen
}