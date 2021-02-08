#include "LevelInterface.hpp"
#include "ConsoleDrawing.cpp"
#include "Sprite.cpp"
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */
vector<int> enemy_possible_moves = {INPUT_DOWN, INPUT_DOWNLEFT, INPUT_DOWNRIGHT};
using namespace std;
Sprite LevelInterface::player;
int LevelInterface::enemySpeed = 1;
int LevelInterface::bonusLimit = 20;
int LevelInterface::enemyLimit = 2;
int LevelInterface::internal_score = 1;
int LevelInterface::bottom_wall_id;
vector<Sprite> LevelInterface::Enemies;
vector<Sprite> LevelInterface::Bonuses;

LevelInterface::LevelInterface()
{
    ConsoleDrawing c;
    this->canvas_handler = c;
    srand(time(NULL));
}

void LevelInterface::setup()
{

    this->level = 1;
    this->score = 1000;
    //hardwriting is a lot faster than cycling through the whole canvas

    //initializing the canvas
    vector<vector<char>> canvas(CANVAS_WIDTH, vector<char>(CANVAS_HEIGHT));

    //hardwriting score and level, they don't need to be sprites. This needs to be done before setting the canvas since im not using Sprite
    canvas.at(PLAYER_WIDTH + 2).at(SCORE_HEIGHT) = 'S';
    canvas.at(PLAYER_WIDTH + 3).at(SCORE_HEIGHT) = 'C';
    canvas.at(PLAYER_WIDTH + 4).at(SCORE_HEIGHT) = 'O';
    canvas.at(PLAYER_WIDTH + 5).at(SCORE_HEIGHT) = 'R';
    canvas.at(PLAYER_WIDTH + 6).at(SCORE_HEIGHT) = 'E';
    canvas.at(PLAYER_WIDTH + 7).at(SCORE_HEIGHT) = ':';
    canvas.at(PLAYER_WIDTH + 8).at(SCORE_HEIGHT) = ' ';
    canvas.at(PLAYER_WIDTH + 9).at(SCORE_HEIGHT) = '1';
    canvas.at(PLAYER_WIDTH + 10).at(SCORE_HEIGHT) = '0';
    canvas.at(PLAYER_WIDTH + 11).at(SCORE_HEIGHT) = '0';
    canvas.at(PLAYER_WIDTH + 12).at(SCORE_HEIGHT) = '0';

    canvas.at(PLAYER_WIDTH + 2).at(SCORE_HEIGHT + 1) = 'L';
    canvas.at(PLAYER_WIDTH + 3).at(SCORE_HEIGHT + 1) = 'E';
    canvas.at(PLAYER_WIDTH + 4).at(SCORE_HEIGHT + 1) = 'V';
    canvas.at(PLAYER_WIDTH + 5).at(SCORE_HEIGHT + 1) = 'E';
    canvas.at(PLAYER_WIDTH + 6).at(SCORE_HEIGHT + 1) = 'L';
    canvas.at(PLAYER_WIDTH + 7).at(SCORE_HEIGHT + 1) = ':';
    canvas.at(PLAYER_WIDTH + 8).at(SCORE_HEIGHT + 1) = ' ';
    canvas.at(PLAYER_WIDTH + 9).at(SCORE_HEIGHT + 1) = '1';

    Sprite::setCanvas(canvas);

    // hardwriting the walls, bottom wall is special since it will make enemies dissappear instead of bounce
    vector<vector<int>> wall_position;
    vector<vector<int>> bottom_wall_position;

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
        bottom_wall_position.push_back({x, CANVAS_HEIGHT - 1, (int)'-'});
    }

    //hardwriting the player
    vector<vector<int>> player_position;
    vector<int> ppoint1 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 3, (int)'|'};
    vector<int> ppoint2 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 4, (int)'A'};
    vector<int> ppoint3 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 5, (int)'|'};
    vector<int> ppoint4 = {PLAYER_STARTING_X + 1, CANVAS_HEIGHT - 4, (int)'-'};
    vector<int> ppoint5 = {PLAYER_STARTING_X - 1, CANVAS_HEIGHT - 4, (int)'^'};
    vector<int> ppoint6 = {PLAYER_STARTING_X - 1, CANVAS_HEIGHT - 3, (int)'0'};
    vector<int> ppoint7 = {PLAYER_STARTING_X + 1, CANVAS_HEIGHT - 3, (int)'0'};
    vector<int> ppoint8 = {PLAYER_STARTING_X + 1, CANVAS_HEIGHT - 5, (int)'0'};
    vector<int> ppoint9 = {PLAYER_STARTING_X - 1, CANVAS_HEIGHT - 5, (int)'0'};
    player_position.push_back(ppoint1);
    player_position.push_back(ppoint2);
    player_position.push_back(ppoint3);
    player_position.push_back(ppoint4);
    player_position.push_back(ppoint5);
    player_position.push_back(ppoint6);
    player_position.push_back(ppoint7);
    player_position.push_back(ppoint8);
    player_position.push_back(ppoint9);

    //hardwriting a single bonus
    // vector<vector<int>> bonus_points;
    // vector<int> bpoint = {30, 1, int('B')};
    // bonus_points.push_back(bpoint);

    //hardwriting two enemies
    // vector<vector<int>> ep1;
    // vector<int> e1point1 = {15, 1, (int)'*'};
    // vector<int> e1point2 = {15, 2, (int)'E'};
    // vector<int> e1point3 = {15, 3, (int)'*'};
    // vector<int> e1point4 = {15 + 1, 2, (int)'*'};
    // vector<int> e1point5 = {15 - 1, 2, (int)'*'};
    // ep1.push_back(e1point1);
    // ep1.push_back(e1point2);
    // ep1.push_back(e1point3);
    // ep1.push_back(e1point4);
    // ep1.push_back(e1point5);

    // vector<vector<int>> ep2;
    // vector<int> e2point1 = {45, 1, (int)'*'};
    // vector<int> e2point2 = {45, 2, (int)'E'};
    // vector<int> e2point3 = {45, 3, (int)'*'};
    // vector<int> e2point4 = {45 + 1, 2, (int)'*'};
    // vector<int> e2point5 = {45 - 1, 2, (int)'*'};
    // ep2.push_back(e2point1);
    // ep2.push_back(e2point2);
    // ep2.push_back(e2point3);
    // ep2.push_back(e2point4);
    // ep2.push_back(e2point5);

    //loading sprites
    Sprite player(player_position, PLAYER);
    Sprite wall(wall_position, WALL);
    Sprite bottom_wall(bottom_wall_position, WALL);
    // Sprite enemy1(ep1, ENEMY);
    // Sprite enemy2(ep2, ENEMY);
    // Sprite bonus(bonus_points, BONUS);
    player.load();
    wall.load();
    bottom_wall.load();
    // enemy1.load();
    // enemy2.load();
    // bonus.load();
    LevelInterface::player = player;
    // LevelInterface::Enemies.push_back(enemy1);
    // LevelInterface::Enemies.push_back(enemy2);
    // LevelInterface::Bonuses.push_back(bonus);
    Sprite::bottom_wall_id = bottom_wall.getSpriteID();
    this->canvas_handler.DrawAtStart(Sprite::getCanvas());
}

void LevelInterface::moveGame()
{
    int direction;
    int after_move;
    for (size_t i = 0; i < Bonuses.size(); i++)
    {
        after_move = Bonuses[i].move(DOWN, 0, 1).first;
        switch (after_move)
        {
        case NOTHING:
            if (Bonuses[i].isNear(player.getSpriteID()))
            {
                Bonuses[i].unload();
                this->addScore(100);
                Bonuses.erase(Bonuses.begin() + i);
            }
            break;
        case UPDATE_SCORE_BONUS:
            this->addScore(100);
            Bonuses.erase(Bonuses.begin() + i);
            break;

        case ERASE:
            Bonuses.erase(Bonuses.begin() + i);
            break;
        }
    }
    for (size_t i = 0; i < Enemies.size(); i++)
    {
        direction = enemy_possible_moves[rand() % 3];
        switch (direction)
        {
        case INPUT_DOWN:
            after_move = Enemies[i].move(DOWN, 0, 1).first;
            break;
        case INPUT_DOWNLEFT:
            after_move = Enemies[i].move(DOWN_LEFT, -1, 1).first;
            break;
        case INPUT_DOWNRIGHT:
            after_move = Enemies[i].move(DOWN_RIGHT, 1, 1).first;
            break;
        }
        switch (after_move)
        {
        case NOTHING:
            if (Enemies[i].isNear(player.getSpriteID()))
            {
                Enemies[i].unload();
                this->removeScore(100);
                Enemies.erase(Enemies.begin() + i);
            }
            break;
        case UPDATE_SCORE_ENEMY:
            this->removeScore(100);
            Enemies.erase(Enemies.begin() + i);
            break;
        case ERASE:
            Enemies.erase(Enemies.begin() + i);
            break;
        }
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
    return;
}

void LevelInterface::movePlayer(int direction)
{
    pair<int, int> after_move;
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
    switch (after_move.first)
    {
    case UPDATE_SCORE_ENEMY:
        this->removeScore(100);
        if (after_move.second != USELESS)
        {
            LevelInterface::removeEnemy(after_move.second);
        }
        break;

    case UPDATE_SCORE_BONUS:
        if (after_move.second != USELESS)
        {
            LevelInterface::removeBonus(after_move.second);
        }
        this->addScore(100);
        break;
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
}

void LevelInterface::removeEnemy(int id)
{
    for (size_t i = 0; i < Enemies.size(); i++)
    {
        if (Enemies[i].getSpriteID() == id)
        {
            Enemies.erase(Enemies.begin() + i);
            return;
        }
    }
}

void LevelInterface::removeBonus(int id)
{
    for (size_t i = 0; i < Bonuses.size(); i++)
    {
        if (Bonuses[i].getSpriteID() == id)
        {
            Bonuses.erase(Bonuses.begin() + i);
            return;
        }
    }
}
void LevelInterface::removeScore(int score)
{
    if (this->score - score < 0)
    {
        this->gameState = GAME_OVER;
        return;
    }
    else if (this->internal_score - score < 0)
    {
        this->internal_score = 1000 - internal_score + score;
        this->level--;
        this->bonusLimit++;
        this->enemyLimit--;
    }
    else
    {
        this->internal_score -= score;
    }
    this->score -= score;
    //updating the score and the level
    vector<vector<char>> temp = Sprite::getCanvas();
    int new_score = this->score;
    int new_level = this->level;
    string score_string = to_string(new_score);
    string level_string = to_string(new_level);
    int score_position = 9;
    int level_position = 9;
    //resetting to 0
    for (size_t i = PLAYER_WIDTH + 9; i < CANVAS_WIDTH - 1; i++)
    {
        temp.at(i).at(SCORE_HEIGHT) = '\0';
        temp.at(i).at(SCORE_HEIGHT + 1) = '\0';
    }
    for (char characther : score_string)
    {
        temp.at(PLAYER_WIDTH + score_position).at(SCORE_HEIGHT) = characther;
        score_position++;
    }
    for (char characther : level_string)
    {
        temp.at(PLAYER_WIDTH + level_position).at(SCORE_HEIGHT + 1) = characther;
        level_position++;
    }
    Sprite::setCanvas(temp);
    return;
}

void LevelInterface::addScore(int score)
{
    if (this->internal_score + score >= 1000)
    {
        this->level++;
        this->internal_score = internal_score + score - 1000;
        if (bonusLimit != 1)
        {
            this->bonusLimit--;
        }
        this->enemyLimit++;
    }
    else
    {
        this->internal_score += score;
    }
    this->score += score;
    //updating the score and the levels
    vector<vector<char>> temp = Sprite::getCanvas();
    int new_score = this->score;
    int new_level = this->level;
    string score_string = to_string(new_score);
    string level_string = to_string(new_level);
    int score_position = 9;
    int level_position = 9;
    //resetting to 0
    for (size_t i = PLAYER_WIDTH + 9; i < CANVAS_WIDTH - 1; i++)
    {
        temp.at(i).at(SCORE_HEIGHT) = '\0';
        temp.at(i).at(SCORE_HEIGHT + 1) = '\0';
    }
    for (char characther : score_string)
    {
        temp.at(PLAYER_WIDTH + score_position).at(SCORE_HEIGHT) = characther;
        score_position++;
    }
    for (char characther : level_string)
    {
        temp.at(PLAYER_WIDTH + level_position).at(SCORE_HEIGHT + 1) = characther;
        level_position++;
    }
    Sprite::setCanvas(temp);
    return;
}

void LevelInterface::spawner()
{
    if (Enemies.size() < enemyLimit)
    {
        int enemy_limit = enemyLimit - Enemies.size();
        for (size_t i = 0; i < enemy_limit; i++)
        {
            int load_check = 0;
            Sprite enemy;
            do
            {
                //rng between 3 and PLAYER_WIDTH - 3
                int x = rand() % ((PLAYER_WIDTH - 2) - 3 + 1) + 3;
                vector<vector<int>> ep1;

                vector<int> e1point1 = {x, 2, (int)'*'};
                vector<int> e1point2 = {x, 3, (int)'E'};
                vector<int> e1point3 = {x, 4, (int)'*'};
                vector<int> e1point4 = {x + 1, 3, (int)'*'};
                vector<int> e1point5 = {x - 1, 3, (int)'*'};
                vector<int> e1point6 = {x - 1, 2, (int)'0'};
                vector<int> e1point7 = {x + 1, 2, (int)'0'};
                vector<int> e1point8 = {x + 1, 4, (int)'0'};
                vector<int> e1point9 = {x - 1, 4, (int)'0'};
                ep1.push_back(e1point1);
                ep1.push_back(e1point2);
                ep1.push_back(e1point3);
                ep1.push_back(e1point4);
                ep1.push_back(e1point5);
                ep1.push_back(e1point6);
                ep1.push_back(e1point7);
                ep1.push_back(e1point8);
                ep1.push_back(e1point9);
                enemy = Sprite(ep1, ENEMY);
                load_check = enemy.load();
            } while (load_check != LOAD_ALLOWED);
            LevelInterface::Enemies.push_back(enemy);
        }
    }
    if (Bonuses.size() < bonusLimit)
    {
        int bonus_limit = bonusLimit - Bonuses.size();
        for (size_t i = 0; i < bonus_limit; i++)
        {
            int bonus_check = 0;
            Sprite bonus;
            do
            {
                //rng between 2 and PLAYER_WIDTH - 1
                int x = rand() % ((PLAYER_WIDTH - 1) - 2 + 1) + 2;
                vector<vector<int>> bonus_points;
                vector<int> bpoint = {x, 1, int('$')};
                bonus_points.push_back(bpoint);
                bonus = Sprite(bonus_points, BONUS);
                bonus_check = bonus.load();
            } while (bonus_check != LOAD_ALLOWED);
            LevelInterface::Bonuses.push_back(bonus);
        }
    }
}

void LevelInterface::gameOver()
{
    vector<vector<char>> temp = Sprite::getCanvas();
    temp.at(PLAYER_WIDTH + 9).at(SCORE_HEIGHT + 5) = 'G';
    temp.at(PLAYER_WIDTH + 10).at(SCORE_HEIGHT + 5) = 'A';
    temp.at(PLAYER_WIDTH + 11).at(SCORE_HEIGHT + 5) = 'M';
    temp.at(PLAYER_WIDTH + 12).at(SCORE_HEIGHT + 5) = 'E';
    temp.at(PLAYER_WIDTH + 9).at(SCORE_HEIGHT + 6) = 'O';
    temp.at(PLAYER_WIDTH + 10).at(SCORE_HEIGHT + 6) = 'V';
    temp.at(PLAYER_WIDTH + 11).at(SCORE_HEIGHT + 6) = 'E';
    temp.at(PLAYER_WIDTH + 12).at(SCORE_HEIGHT + 6) = 'R';
    this->canvas_handler.DrawBuffer(temp);
}