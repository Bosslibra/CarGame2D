#include "Sprite.hpp"
#include <iostream>
using namespace std;
int Sprite::lastUnusedID = 0;
vector<int> Sprite::unloadedIDs;
map<int, vector<int>> Sprite::loadedSprites;
map<int, vector<int>> Sprite::unloadedSprites;

Sprite::Sprite(int x_pos, int y_pos)
{
    this->x = x_pos;
    this->y = y_pos;
    this->spriteID = Sprite::idGenerator();
    Sprite::unloadSprite(x_pos, y_pos, this->spriteID);
}
void Sprite::deleteSprite()
{

    map<int, vector<int>>::iterator it = loadedSprites.find(this->spriteID);
    if (it != loadedSprites.end())
    {
        unloadedIDs.push_back(it->first);
        loadedSprites.erase(it);
    }
    else
    {
        map<int, vector<int>>::iterator it = unloadedSprites.find(this->spriteID);
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

int Sprite::getSpriteX()
{
    return this->x;
}

int Sprite::getSpriteY()
{
    return this->y;
}

bool Sprite::isLoaded()
{
    map<int, vector<int>>::iterator it = loadedSprites.find(this->spriteID);
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
    if (Sprite::isLoaded() == false)
    {
        loadSprite(this->x, this->y, this->spriteID);
    }
}

void Sprite::unload()
{
    if (Sprite::isLoaded() == true)
    {
        unloadSprite(this->x, this->y, this->spriteID);
    }
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

void Sprite::loadSprite(int x, int y, int id)
{
    vector<int> pair;
    pair.push_back(x);
    pair.push_back(y);
    loadedSprites[id] = pair;
     Sprite::removeOldOccurrence(id, OLD_UNLOAD);
}

void Sprite::unloadSprite(int x, int y, int id)
{
    vector<int> pair;
    pair.push_back(x);
    pair.push_back(y);
    unloadedSprites[id] = pair;
    Sprite::removeOldOccurrence(id, OLD_LOAD);
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