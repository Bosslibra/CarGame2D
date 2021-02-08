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
int LevelInterface::mineLimit = 1;
int LevelInterface::internal_score = 1;
int LevelInterface::bottom_wall_id;
vector<Sprite> LevelInterface::Enemies;
vector<Sprite> LevelInterface::Bonuses;
vector<Sprite> LevelInterface::Mines;

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
        if (y != 0 && y != CANVAS_HEIGHT)
        {
            wall_position.push_back({1, y, (int)'#'});
            wall_position.push_back({PLAYER_WIDTH, y, (int)'#'});
        }
    }
    for (int x = 0; x < CANVAS_WIDTH; x++)
    {
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
    //loading sprites
    Sprite player(player_position, PLAYER);
    Sprite wall(wall_position, WALL);
    Sprite bottom_wall(bottom_wall_position, WALL);
    player.load();
    wall.load();
    bottom_wall.load();
    LevelInterface::player = player;
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
    for (size_t i = 0; i < Mines.size(); i++)
    {
        after_move = Mines[i].move(DOWN, 0, 1).first;
        switch (after_move)
        {
        case NOTHING:
            if (Mines[i].isNear(player.getSpriteID()))
            {
                Mines[i].unload();
                this->removeScore(100);
                Mines.erase(Mines.begin() + i);
            }
            break;
        case UPDATE_SCORE_ENEMY:
            this->removeScore(100);
            Mines.erase(Mines.begin() + i);
            break;
        case ERASE:
            Mines.erase(Mines.begin() + i);
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

        case ENEMY_ENEMY_COLLISION:

            break;
        }
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
    return;
}

void LevelInterface::recursive_movement(int last_direction, int id)
{
    int after_move;
    if (last_direction == DOWN_LEFT)
    {
        last_direction = DOWN_RIGHT;
    }
    else if (last_direction == DOWN_RIGHT)
    {
        last_direction = DOWN_LEFT;
    }
    switch (last_direction)
    {
    case INPUT_DOWN:
        after_move = Enemies[id].move(DOWN, 0, 1).first;
        break;
    case INPUT_DOWNLEFT:
        after_move = Enemies[id].move(DOWN_LEFT, -1, 1).first;
        break;
    case INPUT_DOWNRIGHT:
        after_move = Enemies[id].move(DOWN_RIGHT, 1, 1).first;
        break;
    }
    switch (after_move)
    {
    case NOTHING:
        if (Enemies[id].isNear(player.getSpriteID()))
        {
            Enemies[id].unload();
            this->removeScore(100);
            Enemies.erase(Enemies.begin() + id);
        }
        break;
    case UPDATE_SCORE_ENEMY:
        this->removeScore(100);
        Enemies.erase(Enemies.begin() + id);
        break;
    case ERASE:
        Enemies.erase(Enemies.begin() + id);
        break;

    case ENEMY_ENEMY_COLLISION:
        this->recursive_movement(last_direction, id);
        break;
    }
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
            this->removeEnemy(after_move.second);
            this->removeMine(after_move.second);
        }
        break;
    case UPDATE_SCORE_BONUS:
        if (after_move.second != USELESS)
        {
            this->removeBonus(after_move.second);
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

void LevelInterface::removeMine(int id)
{
    for (size_t i = 0; i < Mines.size(); i++)
    {
        if (Mines[i].getSpriteID() == id)
        {
            Mines.erase(Mines.begin() + i);
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
    if (this->score % 1000 == 0)
    {
        internal_score--;
        this->level--;
        this->bonusLimit++;
        this->enemyLimit--;
        this->mineLimit--;
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
    if ((this->score + score) % 1000 == 0)
    {
        int module = (this->score + score) / 1000;
        if (module > internal_score)
        {
            internal_score = module;
            this->level++;
            if (bonusLimit > 5)
            {
                this->bonusLimit--;
            }
            if (enemyLimit < 10)
            {
                this->enemyLimit++;
            }
            this->mineLimit++;
        }
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
        int x;
        Sprite enemy;
        for (size_t i = 0; i < enemy_limit; i++)
        {
            do
            {
                //rng between 3 and PLAYER_WIDTH - 3
                x = rand() % ((PLAYER_WIDTH - 2) - 3 + 1) + 3;
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
            } while (enemy.isOccupied(x, 2) != EMPTY || enemy.isOccupied(x, 3) != EMPTY || enemy.isOccupied(x, 4) != EMPTY ||
                     enemy.isOccupied(x + 1, 3) != EMPTY || enemy.isOccupied(x - 1, 3) != EMPTY || enemy.isOccupied(x - 1, 2) != EMPTY ||
                     enemy.isOccupied(x + 1, 2) != EMPTY || enemy.isOccupied(x + 1, 4) != EMPTY || enemy.isOccupied(x - 1, 4) != EMPTY);
            LevelInterface::Enemies.push_back(enemy);
            enemy.load();
        }
    }
    if (Mines.size() < mineLimit)
    {
        int mine_limit = mineLimit - Mines.size();
        for (size_t i = 0; i < mine_limit; i++)
        {
            int x = rand() % ((PLAYER_WIDTH - 1) - 2 + 1) + 2;
            vector<vector<int>> mine_points;
            vector<int> mpoint = {x, 1, int('M')};
            mine_points.push_back(mpoint);
            Sprite mine = Sprite(mine_points, ENEMY);
            mine.load();
            LevelInterface::Mines.push_back(mine);
        }
    }
    if (Bonuses.size() < bonusLimit)
    {
        int bonus_limit = bonusLimit - Bonuses.size();
        for (size_t i = 0; i < bonus_limit; i++)
        {
            //rng between 2 and PLAYER_WIDTH - 1
            int x = rand() % ((PLAYER_WIDTH - 1) - 2 + 1) + 2;
            vector<vector<int>> bonus_points;
            vector<int> bpoint = {x, 1, int('$')};
            bonus_points.push_back(bpoint);
            Sprite bonus = Sprite(bonus_points, BONUS);
            bonus.load();
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