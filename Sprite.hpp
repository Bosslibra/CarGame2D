#include <vector>
using namespace std;
class Sprite
{
private:
    int x;
    int y;
    static vector<Sprite> loadedSprites;

public:
    Sprite(int x, int y);
    void deleteSprite(int x, int y);
};
