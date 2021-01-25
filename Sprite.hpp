#include <map>
#include <vector>
using namespace std;
class Sprite
{
private:
    int x;
    int y;
    int spriteID;
    static int lastUnusedID;
    static map<int, vector<int>> loadedSprites;

public:
    Sprite(int x, int y, int spriteID);
    void deleteSprite(int spriteID);
    int getSpriteID();
};
