#include <Sprite.hpp>
using namespace std;
int Sprite::lastUnusedID = 0;

Sprite::Sprite(int x_pos, int y_pos, int spriteID_const)
{
    this->x = x_pos;
    this->y = y_pos;
    this->spriteID = lastUnusedID;
    vector<int> pair;
    pair.push_back(x);
    pair.push_back(y);
    loadedSprites[lastUnusedID] = pair;
    lastUnusedID++;
}
void Sprite::deleteSprite(int spriteID)
{
    map<int, vector<int>>::iterator it = loadedSprites.find(spriteID);
    if (it != loadedSprites.end())
    {
        loadedSprites.erase(it);
    }
}

int Sprite::getSpriteID()
{
    return this->spriteID;
}