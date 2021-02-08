//TODO check that the direction are actually correct...

#include "Sprite.hpp"
using namespace std;
int Sprite::lastUnusedID = 0;
vector<int> Sprite::unloadedIDs;
map<int, Sprite> Sprite::loadedSprites;
vector<vector<char>> Sprite::canvas;
int Sprite::canvas_height;
int Sprite::canvas_width;
int Sprite::bottom_wall_id;

Sprite::Sprite()
{
    //empty constructor
}

Sprite::Sprite(vector<vector<int>> positions, int type, int spriteID)
{
    this->positions = positions;
    this->spriteID = spriteID;
    this->type = type;
}

Sprite::Sprite(vector<vector<int>> positions, int type)
{
    this->positions = positions;
    this->spriteID = Sprite::idGenerator();
    this->type = type;
}

Sprite Sprite::getLoadedSprite(int spriteID)
{
    map<int, Sprite>::iterator it = loadedSprites.find(spriteID);
    if (it != loadedSprites.end())
    {
        return it->second;
    }
    else
    {
        Sprite notfound;
        notfound.spriteID = -1;
        return notfound;
    }
}

int Sprite::getSpriteID()
{
    return this->spriteID;
}

vector<vector<char>> Sprite::getCanvas()
{
    return canvas;
}

void Sprite::setCanvas(vector<vector<char>> new_canvas)
{
    canvas = new_canvas;
    canvas_height = new_canvas[0].size();
    canvas_width = new_canvas.size();
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

void Sprite::load()
{
    // bool check = false;
    //checking that every point is not occupied
    // for (vector<int> coordinates : this->positions)
    // {
    //     int sprite_id = this->isOccupied(coordinates[X_SPRITE], coordinates[Y_SPRITE]);
    //     if (sprite_id != EMPTY)
    //     {
    //         check = true;
    //     }
    // }
    //every point is not occupied, writing the sprite
    // if (check)
    // {
    for (vector<int> coordinates : this->positions)
    {
        canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = coordinates[CHAR_SPRITE];
    }
    loadedSprites[this->spriteID] = *this;
    return;
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

void Sprite::unloadSprite()
{
    for (vector<int> coordinates : this->positions)
    {
        canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = char(0);
    }
    map<int, Sprite>::iterator it = loadedSprites.find(this->spriteID);
    if (it != loadedSprites.end())
    {
        loadedSprites.erase(it);
    }
    return;
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

pair<int, int> Sprite::oobCheck()
{
    if (this->type == PLAYER)
    {
        return make_pair(PLAYER_OOB, USELESS);
    }
    else if (this->type == ENEMY)
    {
        return make_pair(ENEMY_OOB, USELESS);
    }
    else if (this->type == BONUS)
    {
        return make_pair(BONUS_OOB, USELESS);
    }
}

pair<int, int> Sprite::internalCollisionCheck(int occupied_id, int occupied_type)
{
    if (this->type == PLAYER)
    {
        switch (occupied_type)
        {
        case WALL:
            return make_pair(PLAYER_WALL_COLLISION, occupied_id);
            break;

        case ENEMY:
            return make_pair(PLAYER_ENEMY_COLLISION, occupied_id);
            break;

        case BONUS:
            return make_pair(PLAYER_BONUS_COLLISION, occupied_id);
            break;
        }
    }
    else if (this->type == ENEMY)
    {
        switch (occupied_type)
        {
        case WALL:
            if (occupied_id == bottom_wall_id)
            {
                return make_pair(ENEMY_BOTTOM_WALL_COLLISION, occupied_id);
                break;
            }
            else
            {
                return make_pair(ENEMY_WALL_COLLISION, occupied_id);
                break;
            }
        case ENEMY:
            return make_pair(ENEMY_ENEMY_COLLISION, occupied_id);
        }
    }
    else if (this->type == BONUS)
    {
        switch (occupied_type)
        {
        case WALL:
            if (occupied_id == bottom_wall_id)
            {
                return make_pair(BONUS_BOTTOM_WALL_COLLISION, occupied_id);
            }
            else
            {
                return make_pair(BONUS_WALL_COLLISION, occupied_id);
            }
            break;
        case ENEMY:
            return make_pair(BONUS_ENEMY_COLLISION, occupied_id);
            break;
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

    //MEMO [x][y], [0][0] is the top-left point
    vector<vector<int>> current_sprite_positions = this->positions;
    switch (direction)
    {
    case UP:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE], coordinates[Y_SPRITE] + unit_y);
            if (coordinates[Y_SPRITE] + unit_y < 0)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case UP_RIGHT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE] + unit_y);
            if (coordinates[X_SPRITE] + unit_x > canvas_width || coordinates[Y_SPRITE] + unit_y < 0)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case RIGHT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE]);
            if (coordinates[X_SPRITE] + unit_x > canvas_width)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN_RIGHT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE] + unit_y);
            if (coordinates[X_SPRITE] + unit_x > canvas_width || coordinates[Y_SPRITE] + unit_y > canvas_height)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE], coordinates[Y_SPRITE] + unit_y);
            if (coordinates[Y_SPRITE] + unit_y > canvas_height)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case DOWN_LEFT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE] + unit_y);
            if (coordinates[X_SPRITE] + unit_x < 0 || coordinates[Y_SPRITE] + unit_y > canvas_height)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case LEFT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE]);
            if (coordinates[X_SPRITE] + unit_x < 0)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;

    case UP_LEFT:
        for (vector<int> coordinates : current_sprite_positions)
        {
            int occupied_id = this->isOccupied(coordinates[X_SPRITE] + unit_x, coordinates[Y_SPRITE] + unit_y);
            if (coordinates[X_SPRITE] + unit_x < 0 || coordinates[Y_SPRITE] + unit_y < 0)
            {
                return this->oobCheck();
            }
            else if (occupied_id != EMPTY)
            {
                return this->internalCollisionCheck(occupied_id, this->getLoadedSprite(occupied_id).type);
            }
        }
        return make_pair(MOVE_ALLOWED, USELESS);
        break;
    }
}

int Sprite::isOccupied(int x, int y)
{
    int check = EMPTY;
    for (map<int, Sprite>::iterator it = loadedSprites.begin(); it != loadedSprites.end(); ++it)
    {
        if (it->first != this->spriteID)
        {
            for (vector<int> coordinates : it->second.positions)
            {
                if (coordinates[X_SPRITE] == x)
                {
                    if (coordinates[Y_SPRITE] == y)
                    {
                        return it->first;
                    }
                }
            }
        }
    }
    return check;
}

bool Sprite::isNear(int id)
{
    vector<vector<int>> player_position = Sprite::getLoadedSprite(id).positions;
    for (vector<int> coordinates_sprite : this->positions)
    {
        for (vector<int> coordinates_player : player_position)
        {
            if (coordinates_player[0] - coordinates_sprite[0] == 1 || coordinates_player[0] - coordinates_sprite[0] == -1 || coordinates_player[0] - coordinates_sprite[0] == 0)
            {
                if (coordinates_player[1] - coordinates_sprite[1] == 1 || coordinates_player[1] - coordinates_sprite[1] == -1 || coordinates_player[1] - coordinates_sprite[1] == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

pair<int, int> Sprite::move(int direction, int unit_x, int unit_y)
{
    pair<int, int> check = this->checkCollision(direction, unit_x, unit_y);
    vector<vector<int>> new_positions;
    Sprite temp;
    switch (check.first)
    {
    case MOVE_ALLOWED:
        for (vector<int> coordinates : this->positions)
        {
            //deleting the old position
            canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = char(0);
        }
        for (vector<int> coordinates : this->positions)
        {
            //moving the point to the new position
            canvas.at(coordinates[X_SPRITE] + unit_x).at(coordinates[Y_SPRITE] + unit_y) = coordinates[CHAR_SPRITE];
            //updating the Sprite position
            coordinates.at(X_SPRITE) += unit_x;
            coordinates.at(Y_SPRITE) += unit_y;
            vector<int> temp = {coordinates.at(X_SPRITE), coordinates.at(Y_SPRITE), coordinates.at(CHAR_SPRITE)};
            new_positions.push_back(temp);
        }
        loadedSprites[this->spriteID].positions = new_positions;
        this->positions = new_positions;
        return make_pair(NOTHING, USELESS);
        break;

    case PLAYER_WALL_COLLISION:
        //nothing should happen
        return make_pair(NOTHING, USELESS);
        break;

    case PLAYER_ENEMY_COLLISION:
        temp = Sprite::getLoadedSprite(check.second);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        for (vector<int> coordinates : this->positions)
        {
            //deleting the old position
            canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = char(0);
        }
        for (vector<int> coordinates : this->positions)
        {
            //moving the point to the new position
            canvas.at(coordinates[X_SPRITE] + unit_x).at(coordinates[Y_SPRITE] + unit_y) = coordinates[CHAR_SPRITE];
            //updating the Sprite position
            coordinates.at(X_SPRITE) += unit_x;
            coordinates.at(Y_SPRITE) += unit_y;
            vector<int> temp = {coordinates.at(X_SPRITE), coordinates.at(Y_SPRITE), coordinates.at(CHAR_SPRITE)};
            new_positions.push_back(temp);
        }
        loadedSprites[this->spriteID].positions = new_positions;
        this->positions = new_positions;
        return make_pair(UPDATE_SCORE_ENEMY, check.second);
        break;

    case PLAYER_BONUS_COLLISION:
        temp = Sprite::getLoadedSprite(check.second);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        for (vector<int> coordinates : this->positions)
        {
            //deleting the old position
            canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = char(0);
        }
        for (vector<int> coordinates : this->positions)
        {
            //moving the point to the new position
            canvas.at(coordinates[X_SPRITE] + unit_x).at(coordinates[Y_SPRITE] + unit_y) = coordinates[CHAR_SPRITE];
            //updating the Sprite position
            coordinates.at(X_SPRITE) += unit_x;
            coordinates.at(Y_SPRITE) += unit_y;
            vector<int> temp = {coordinates.at(X_SPRITE), coordinates.at(Y_SPRITE), coordinates.at(CHAR_SPRITE)};
            new_positions.push_back(temp);
        }
        loadedSprites[this->spriteID].positions = new_positions;
        this->positions = new_positions;
        return make_pair(UPDATE_SCORE_BONUS, check.second);
        break;

    case ENEMY_WALL_COLLISION:
        //enemy has hit a wall, handler must change its direction
        //nothing should happen
        return make_pair(NOTHING, USELESS);
        break;

    case ENEMY_BOTTOM_WALL_COLLISION:
        //enemy sprite disappears;
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        return make_pair(ERASE, USELESS);
        break;

    case ENEMY_ENEMY_COLLISION:
        for (vector<int> coordinates : this->positions)
        {
            //deleting the old position
            canvas.at(coordinates[X_SPRITE]).at(coordinates[Y_SPRITE]) = char(0);
        }
        for (vector<int> coordinates : this->positions)
        {
            //moving the point to the new position
            canvas.at(coordinates[X_SPRITE] + unit_x).at(coordinates[Y_SPRITE] + unit_y) = coordinates[CHAR_SPRITE];
            //updating the Sprite position
            coordinates.at(X_SPRITE) += unit_x;
            coordinates.at(Y_SPRITE) += unit_y;
            vector<int> temp = {coordinates.at(X_SPRITE), coordinates.at(Y_SPRITE), coordinates.at(CHAR_SPRITE)};
            new_positions.push_back(temp);
        }
        loadedSprites[this->spriteID].positions = new_positions;
        this->positions = new_positions;
        return make_pair(NOTHING, USELESS);
        break;

    case BONUS_WALL_COLLISION:
        //bonus has to disappear
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        return make_pair(ERASE, USELESS);
        break;

    case BONUS_ENEMY_COLLISION:
        //bonus has to disappear
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        else
        {
            return make_pair(ERASE, USELESS);
        }
        return make_pair(ERASE, USELESS);
        break;

    case BONUS_BOTTOM_WALL_COLLISION:
        //bonus has to disappear
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        else
        {
            return make_pair(ERASE, USELESS);
        }
        return make_pair(ERASE, USELESS);
        break;

    case ENEMY_OOB:
        //enemy has to disappear
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        else
        {

            return make_pair(ERASE, USELESS);
        }
        return make_pair(NOTHING, USELESS);
        break;

    case BONUS_OOB:
        //bonus has to disappear
        temp = Sprite::getLoadedSprite(this->spriteID);
        if (temp.getSpriteID() != -1)
        {
            temp.unload();
        }
        else
        {
            return make_pair(ERASE, USELESS);
        }
        return make_pair(NOTHING, USELESS);
        break;

    case PLAYER_OOB:
        //nothing should happens, same as player against wall
        return make_pair(NOTHING, USELESS);
        break;
    }
}