#include "LevelInterface.hpp"
#include "ConsoleDrawing.cpp"
#include "Sprite.cpp"
using namespace std;
Sprite LevelInterface::player;

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
    vector<int> point1 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 3, (int)'*'};
    vector<int> point2 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 4, (int)'P'};
    vector<int> point3 = {PLAYER_STARTING_X, CANVAS_HEIGHT - 5, (int)'*'};
    vector<int> point4 = {PLAYER_STARTING_X + 1, CANVAS_HEIGHT - 4, (int)'*'};
    vector<int> point5 = {PLAYER_STARTING_X - 1, CANVAS_HEIGHT - 4, (int)'*'};
    player_position.push_back(point1);
    player_position.push_back(point2);
    player_position.push_back(point3);
    player_position.push_back(point4);
    player_position.push_back(point5);
    Sprite player(player_position, PLAYER);
    Sprite wall(wall_position, WALL);
    player.load();
    wall.load();
    LevelInterface::player = player;
    this->canvas_handler.DrawAtStart(Sprite::getCanvas());
}

void LevelInterface::moveGame()
{
}

void LevelInterface::movePlayer(int direction)
{
    switch (direction)
    {
    case INPUT_TOP:
        LevelInterface::player.move(UP, 0, -1);
        break;
    case INPUT_LEFT:
        LevelInterface::player.move(LEFT, -1, 0);
        break;
    case INPUT_RIGHT:
        LevelInterface::player.move(RIGHT, 1, 0);
        break;
    case INPUT_DOWN:
        LevelInterface::player.move(DOWN, 0, 1);
        break;
    case INPUT_TOPLEFT:
        LevelInterface::player.move(UP_LEFT, -1, -1);
        break;
    case INPUT_TOPRIGHT:
        LevelInterface::player.move(UP_RIGHT, 1, -1);
        break;
    case INPUT_DOWNLEFT:
        LevelInterface::player.move(DOWN_LEFT, -1, 1);
        break;
    case INPUT_DOWNRIGHT:
        LevelInterface::player.move(DOWN_RIGHT, 1, 1);
        break;
    }
    this->canvas_handler.DrawBuffer(Sprite::getCanvas());
}

void LevelInterface::updateScore(int score)
{
}

void LevelInterface::updateLevel(int level)
{
}

void LevelInterface::increaseEnemies(){};
void LevelInterface::decreaseEnemies(){};
void LevelInterface::increaseBonuses(){};
void LevelInterface::decreaseBonuses(){};
