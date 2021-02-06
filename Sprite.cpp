#include "Sprite.hpp"
using namespace std;
int Sprite::lastUnusedID = 0;
vector<int> Sprite::unloadedIDs;
map<int, Sprite> Sprite::loadedSprites;
map<int, Sprite> Sprite::unloadedSprites;
vector<vector<char>> Sprite::canvas;
int Sprite::canvas_height;
int Sprite::canvas_width;

Sprite::Sprite(vector<pair<pair<int, int>, char>> positions, int type)
{
    this->positions = positions;
    this->spriteID = Sprite::idGenerator();
    this->type = type;
    Sprite::unloadSprite();
}
void Sprite::deleteSprite()
{
    map<int, Sprite>::iterator it = loadedSprites.find(this->spriteID);
    if (it != loadedSprites.end())
    {
        unloadedIDs.push_back(it->first);
        loadedSprites.erase(it);
    }
    else
    {
        map<int, Sprite>::iterator it = unloadedSprites.find(this->spriteID);
        if (it != unloadedSprites.end())
        {
            unloadedIDs.push_back(it->first);
            unloadedSprites.erase(it);
        }
    }
}

Sprite Sprite::getLoadedSprite(int spriteID)
{
    map<int, Sprite>::iterator it = loadedSprites.find(spriteID);
    if (it != loadedSprites.end())
    {
        return it->second;
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
    map<int, Sprite>::iterator it = loadedSprites.find(this->spriteID);
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
        return this->loadSprite();
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
        this->unloadSprite();
        return UNLOAD_ALLOWED;
    }
    else
    {
        return UNLOAD_SPRITE_WAS_NOT_LOADED;
    }
}

int Sprite::loadSprite()
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
    loadedSprites[this->spriteID] = unloadedSprites[this->spriteID];
    Sprite::removeOldOccurrence(this->spriteID, OLD_UNLOAD);
    return LOAD_ALLOWED;
}

void Sprite::unloadSprite()
{
    for (pair<pair<int, int>, char> pair_father : this->positions)
    {
        pair<int, int> point_coordinate = pair_father.first;
        canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
    }
    unloadedSprites[this->spriteID] = loadedSprites[this->spriteID];
    Sprite::removeOldOccurrence(this->spriteID, OLD_LOAD);
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

pair<int, int> Sprite::oobCheck(int type)
{
    if (this->type == PLAYER)
    {
        return make_pair(ERROR_MOVE_NOT_ALLOWED, USELESS);
    }
    else if (this->type == ENEMY)
    {
        return make_pair(ENEMY_OOB, USELESS);
    }
    else if (this->type == BONUS)
    {
        return make_pair(BONUS_OOB, USELESS);
    }
    else
    {
        return make_pair(ERROR_MOVE_NOT_ALLOWED, USELESS);
    }
}

pair<int, int> Sprite::internalCollisionCheck(int occupied_id, int occupied_type)
{
    if (this->type == PLAYER)
    {
        switch (occupied_type)
        {
        case ENEMY:
            return make_pair(PLAYER_ENEMY_COLLISION, occupied_id);
            break;
        case BONUS:
            return make_pair(PLAYER_BONUS_COLLISION, occupied_id);
            break;
        case WALL:
            return make_pair(PLAYER_WALL_COLLISION, occupied_id);
            break;
        }
    }
    else if (this->type == ENEMY)
    {
        switch (occupied_type)
        {
        case WALL:
            return make_pair(ENEMY_WALL_COLLISION, occupied_id);
            break;
        case BONUS:
            return make_pair(ENEMY_BONUS_COLLISION, occupied_id);
            break;
        case PLAYER:
            return make_pair(ENEMY_PLAYER_COLLISION, occupied_id);
        }
    }
    else if (this->type == BONUS)
    {
        switch (occupied_type)
        {
        case WALL:
            return make_pair(BONUS_WALL_COLLISION, occupied_id);
            break;
        case ENEMY:
            return make_pair(BONUS_ENEMY_COLLISION, occupied_id);
            break;
        case PLAYER:
            return make_pair(BONUS_PLAYER_COLLISION, USELESS);
        }
    }
}

pair<int, int> Sprite::checkCollision(int direction, int unit_x, int unit_y)
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
        return make_pair(ERROR_EMPTY_CANVAS, USELESS);
    }
    vector<pair<pair<int, int>, char>> current_sprite_positions = this->positions;
    switch (direction)
    {
    case UP:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first, pair.second - unit_y, this->spriteID);
            if (pair.second - unit_y < 0)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case UP_RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first + unit_x, pair.second - unit_y, this->spriteID);
            if (pair.first + unit_x > canvas_width || pair.second - unit_y < 0)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first + unit_x, pair.second, this->spriteID);
            if (pair.first + unit_x > canvas_width)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN_RIGHT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first + unit_x, pair.second + unit_y, this->spriteID);
            if (pair.first + unit_x > canvas_width || pair.second + unit_y > canvas_height)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first, pair.second + unit_y, this->spriteID);
            if (pair.second + unit_y > canvas_height)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN_LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first - unit_x, pair.second + unit_y, this->spriteID);
            if (pair.first - unit_x < 0 || pair.second + unit_y > canvas_height)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first - unit_x, pair.second, this->spriteID);
            if (pair.first - unit_x < 0)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case UP_LEFT:
        for (pair<pair<int, int>, char> pair_father : current_sprite_positions)
        {
            pair<int, int> pair = pair_father.first;
            int occupied_id = Sprite::isOccupied(pair.first - unit_x, pair.second - unit_y, this->spriteID);
            if (pair.first - unit_x < 0 || pair.second - unit_y < 0)
            {
                return Sprite::oobCheck(this->type);
            }
            else if (occupied_id != EMPTY)
            {
                return Sprite::internalCollisionCheck(occupied_id, Sprite::getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;
    }
}

int Sprite::isOccupied(int x, int y, int self_id)
{
    int check = EMPTY;
    for (map<int, Sprite>::iterator it = loadedSprites.begin(); it != loadedSprites.end(); ++it)
    {
        if (it->first != self_id)
        {
            for (pair<pair<int, int>, char> pair_father : it->second.positions)
            {
                pair<int, int> pair = pair_father.first;
                if (pair.first == x)
                {
                    if (pair.second == y)
                    {
                        check = it->first;
                    }
                }
            }
        }
    }
    return check;
}

int Sprite::move(int direction, int unit_x, int unit_y)
{
    pair<int, int> check = Sprite::checkCollision(direction, unit_x, unit_y);
    switch (check.first)
    {
    case MOVE_ALLOWED:
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char point = pair_father.second;
            //deleting the old position
            canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
            //moving the point to the new position
            canvas.at(point_coordinate.second + unit_y).at(point_coordinate.first + unit_x) = point;
            //updating the Sprite position
            pair_father.first.first += unit_x;
            pair_father.first.second += unit_y;
        }
        return NOTHING;
        break;

    case PLAYER_ENEMY_COLLISION:
        //player moves, enemy sprite disappears, handler must update score
        Sprite::getLoadedSprite(check.second).unload();
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char point = pair_father.second;
            //deleting the old position
            canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
            //moving the point to the new position
            canvas.at(point_coordinate.second + unit_y).at(point_coordinate.first + unit_x) = point;
            //updating the Sprite position
            pair_father.first.first += unit_x;
            pair_father.first.second += unit_y;
        }
        return UPDATE_SCORE_ENEMY;
        break;
    case PLAYER_WALL_COLLISION:
        //nothing should happen
        break;

    case PLAYER_BONUS_COLLISION:
        //player moves, bonus sprite disappears, handler must update score
        Sprite::getLoadedSprite(check.second).unload();
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char point = pair_father.second;
            //deleting the old position
            canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
            //moving the point to the new position
            canvas.at(point_coordinate.second + unit_y).at(point_coordinate.first + unit_x) = point;
            //updating the Sprite position
            pair_father.first.first += unit_x;
            pair_father.first.second += unit_y;
        }
        return UPDATE_SCORE_BONUS;
        break;

    case ENEMY_WALL_COLLISION:
        //enemy has hit a wall, handler must change its direction
        return BOUNCE_ENEMY;
        break;

    case ENEMY_BONUS_COLLISION:
        //bonus disappears, enemy moves
        Sprite::getLoadedSprite(check.second).unload();
        for (pair<pair<int, int>, char> pair_father : this->positions)
        {
            pair<int, int> point_coordinate = pair_father.first;
            char point = pair_father.second;
            //deleting the old position
            canvas.at(point_coordinate.second).at(point_coordinate.first) = char(0);
            //moving the point to the new position
            canvas.at(point_coordinate.second + unit_y).at(point_coordinate.first + unit_x) = point;
            //updating the Sprite position
            pair_father.first.first += unit_x;
            pair_father.first.second += unit_y;
        }
        break;

    case ENEMY_PLAYER_COLLISION:
        //enemy sprite disappears, handler must update score
        Sprite::getLoadedSprite(this->spriteID).unload();
        return UPDATE_SCORE_ENEMY;
        break;

    case BONUS_WALL_COLLISION:
        //bonus has to disappear
        Sprite::getLoadedSprite(this->spriteID).unload();

        break;
    case BONUS_PLAYER_COLLISION:
        //bonus has to disappear, handler must update score
        Sprite::getLoadedSprite(this->spriteID).unload();
        return UPDATE_SCORE_BONUS;
        break;

    case BONUS_ENEMY_COLLISION:
        //bonus has to disappear
        Sprite::getLoadedSprite(this->spriteID).unload();
        break;

    case ENEMY_OOB:
        //enemy has to disappear
        Sprite::getLoadedSprite(this->spriteID).unload();
        break;

    case BONUS_OOB:
        //bonus has to disappear
        Sprite::getLoadedSprite(this->spriteID).unload();
        break;

    case ERROR_EMPTY_CANVAS:
        //TODO critical error, canvas was not set properly
        break;
    }
}