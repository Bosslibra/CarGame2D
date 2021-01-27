#include "Sprite.hpp"
using namespace std;
int Sprite::lastUnusedID = 0;
vector<int> Sprite::unloadedIDs;
map<int, vector<pair<pair<int, int>, char>>> Sprite::loadedSprites;
map<int, vector<pair<pair<int, int>, char>>> Sprite::unloadedSprites;
vector<vector<char>> Sprite::canvas;
int Sprite::canvas_height;
int Sprite::canvas_width;

Sprite::Sprite(vector<pair<pair<int, int>, char>> positions)
{
    this->positions = positions;
    this->spriteID = Sprite::idGenerator();
    Sprite::unloadSprite(positions, this->spriteID);
}
void Sprite::deleteSprite()
{
    map<int, vector<pair<pair<int, int>, char>>>::iterator it = loadedSprites.find(this->spriteID);
    if (it != loadedSprites.end())
    {
        unloadedIDs.push_back(it->first);
        loadedSprites.erase(it);
    }
    else
    {
        map<int, vector<pair<pair<int, int>, char>>>::iterator it = unloadedSprites.find(this->spriteID);
        if (it != unloadedSprites.end())
        {
            unloadedIDs.push_back(it->first);
            unloadedSprites.erase(it);
        }
    }
}

int Sprite::getSpriteID()
{
    return this->spriteID;
}

void Sprite::setCanvas(vector<vector<char>> new_canvas)
{
    canvas = new_canvas;
    canvas_width = new_canvas[0].size();
    canvas_height = new_canvas.size();
}

bool Sprite::isLoaded()
{
    map<int, vector<pair<pair<int, int>, char>>>::iterator it = loadedSprites.find(this->spriteID);
    if (it != loadedSprites.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Sprite::load()
{
    if (Sprite::isLoaded() == false && !canvas.empty())
    {
        return loadSprite(this->positions, this->spriteID);
    }
    else
    {
        return LOAD_ERROR;
    }
}

int Sprite::unload()
{
    if (Sprite::isLoaded() == true)
    {
        unloadSprite(this->positions, this->spriteID);
        return UNLOAD_ALLOWED;
    }
    else
    {
        return UNLOAD_SPRITE_WAS_NOT_LOADED;
    }
}

int Sprite::loadSprite(vector<pair<pair<int, int>, char>> positions, int id)
{
    bool check = false;
    //checking that every point is not occupied
    for (pair<pair<int, int>, char> pair_father : this->positions)
    {
        pair<int, int> point_coordinate = pair_father.first;
        if (Sprite::isOccupied(point_coordinate.first, point_coordinate.second, this->spriteID))
        {
            check = true;
        }
    }
    //every point is not occupied, writing the sprite
    if (check)
    {
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char element = pair_father.second;
            canvas.at(point_coordinate.second).at(point_coordinate.first) = element;
        }
    }
    else
    {
        return LOAD_OVERLAP;
    }
    loadedSprites[id] = positions;
    Sprite::removeOldOccurrence(id, OLD_UNLOAD);
    return LOAD_ALLOWED;
}

void Sprite::unloadSprite(vector<pair<pair<int, int>, char>> positions, int id)
{
    for (pair<pair<int, int>, char> pair_father : this->positions)
    {
        pair<int, int> point_coordinate = pair_father.first;
        canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
    }
    unloadedSprites[id] = positions;
    Sprite::removeOldOccurrence(id, OLD_LOAD);
}

int Sprite::idGenerator()
{
    if (unloadedIDs.size() == 0)
    {
        int temp = lastUnusedID;
        lastUnusedID++;
        return temp;
    }
    else
    {
        int temp = unloadedIDs.back();
        unloadedIDs.pop_back();
        return temp;
    }
}

void Sprite::removeOldOccurrence(int id, int type)
{
    if (type == OLD_LOAD)
    {
        loadedSprites.erase(id);
    }
    else if (type == OLD_UNLOAD)
    {
        unloadedSprites.erase(id);
    }
}

void Sprite::setPosition(vector<pair<pair<int, int>, char>> positions)
{
    //TODO if the sprite is loaded, check if the new positions are valid
    this->positions = positions;
}

int Sprite::checkCollision(int direction, int unit_x, int unit_y)
{
    //TODO it's not necessary to check every point for collision(example: if a cube goes UP,
    //you just need to check for the top side) but I don't know how to program that by generalizing the
    //form of the Sprite, so I'll just make the Sprite  check every other occupied spot that's not part
    //of him
    //also direction is useless, it's  used because it's easier to check for collisions and probably
    //it's less CPU intensive, for all that it matters...

    //MEMO [y][x], [0][0] is the top-left point
    if (canvas.empty())
    {
        return ERROR_EMPTY_CANVAS;
    }
    vector<pair<pair<int, int>, char>> current_sprite_positions = this->positions;
    switch (direction)
    {
    case UP:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.second - unit_y < 0 || Sprite::isOccupied(pair.first, pair.second - unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case UP_RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first + unit_x > canvas_width || pair.second - unit_y < 0 || Sprite::isOccupied(pair.first + unit_x, pair.second - unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first + unit_x > canvas_width || Sprite::isOccupied(pair.first + unit_x, pair.second, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case DOWN_RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first + unit_x > canvas_width || pair.second + unit_y > canvas_height || Sprite::isOccupied(pair.first + unit_x, pair.second + unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case DOWN:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.second + unit_y > canvas_height || Sprite::isOccupied(pair.first, pair.second + unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case DOWN_LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first - unit_x < 0 || pair.second + unit_y > canvas_height || Sprite::isOccupied(pair.first - unit_x, pair.second + unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first - unit_x < 0 || Sprite::isOccupied(pair.first - unit_x, pair.second, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;

    case UP_LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            if (pair.first - unit_x < 0 || pair.second - unit_y < 0 || Sprite::isOccupied(pair.first - unit_x, pair.second - unit_y, this->spriteID))
            {
                return ERROR_MOVE_NOT_ALLOWED;
            }
        }
        return MOVE_ALLOWED;
        break;
    }
}

bool Sprite::isOccupied(int x, int y, int self_id)
{
    bool check = false;
    for (map<int, vector<pair<pair<int, int>, char>>>::iterator it = loadedSprites.begin(); it != loadedSprites.end(); ++it)
    {
        if (it->first != self_id)
        {
            for (pair<pair<int, int>, char> pair_father : it->second)
            {
                pair<int, int> pair = pair_father.first;
                if (pair.first == x)
                {
                    if (pair.second == y)
                    {
                        check = true;
                    }
                }
            }
        }
    }
    return check;
}

int Sprite::move(int direction, int unit_x, int unit_y)
{
    int check = Sprite::checkCollision(direction, unit_x, unit_y);
    if (check == MOVE_ALLOWED)
    {
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char point = pair_father.second;
            //deleting the old position
            canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
            //moving the point to the new position
            canvas.at(point_coordinate.second + unit_y).at(point_coordinate.first + unit_x) = point;
            //updating the Sprite position
            point_coordinate.first += unit_x;
            point_coordinate.second += unit_y;
        }
    }
    else
    {
        return check;
    }
}