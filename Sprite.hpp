#include <map>
#include <vector>
#define OLD_LOAD 0
#define OLD_UNLOAD 1
using namespace std;
class Sprite
{
private:
    int x;                                        //x position of the sprite
    int y;                                        //y position of the sprite
    int spriteID;                                 //unique identifier
    static int lastUnusedID;                      //last unused identifier
    static vector<int> unloadedIDs;               //vector of identifier that have been unloaded by some sprite, useful to avoid overflow of the spriteID integer
    static map<int, vector<int>> loadedSprites;   //vector of sprites actually loaded in the canvas
    static map<int, vector<int>> unloadedSprites; //vector of sprites that exist but aren't loaded yet
    int idGenerator();                            //returns an unique identifier, using unloadedIDs if some exists or by advancing lastUnusedID
    void loadSprite(int x, int y, int id);        //utility to insert in the loadedSprites map
    void unloadSprite(int x, int y, int id);      //utility to insert in the unloadedSprites map
    void removeOldOccurrence(int id, int type);   //utility to remove the old Sprite occurrence in case a loaded sprite gets unloaded or vice versa

public:
    Sprite(int x, int y); //constructor
    void deleteSprite();  //deletes a sprite
    int getSpriteID();    //returns sprite identifier
    int getSpriteX();     //returns sprite x position
    int getSpriteY();     //returns sprite y position
    bool isLoaded();      //returns true if the sprite is inside the loadedSprites vector
    void load();          //pushes a Sprite into the loadedSprites vector, deleting it from the unloadedSprites if needed
    void unload();        //pushes a Sprite into the unloadedSprites vector, deleting it from the loadedSprites if needed
};
