#include <map>
#include <vector>
#include <tuple>
#include <string>

//macros
#define UP 0
#define UP_RIGHT 1
#define RIGHT 2
#define DOWN_RIGHT 3
#define DOWN 4
#define DOWN_LEFT 5
#define LEFT 6
#define UP_LEFT 7
#define OLD_LOAD 8
#define OLD_UNLOAD 9
#define MOVE_ALLOWED 10
#define LOAD_ALLOWED 11
#define UNLOAD_ALLOWED 12

//errors
#define ERROR_EMPTY_CANVAS 13
#define ERROR_MOVE_NOT_ALLOWED 14
#define LOAD_ERROR 15
#define LOAD_OVERLAP 16
#define UNLOAD_SPRITE_WAS_NOT_LOADED 17

using namespace std;

class Sprite
{
private:
    static int canvas_height;                                               //canvas height, calculated once when a canvas is set, used to check for out of bounds
    static int canvas_width;                                                //canvas width, calculated once when a canvas is set, used to check for out of bounds
    static vector<vector<char>> canvas;                                     //this class assumes that every sprite is placed in the same canvas, which will always be the case in this project
    vector<pair<pair<int, int>, char>> positions;                           //vector of pairs(x,y) that define which point of the matrix are being used for that specific char
    int spriteID;                                                           //unique identifier
    int type;                                                               //bonus or enemy
    static int lastUnusedID;                                                //last unused identifier
    int idGenerator();                                                      //returns an unique identifier, using unloadedIDs if some exists or by advancing lastUnusedID
    int loadSprite(vector<pair<pair<int, int>, char>> positions, int id);   //utility to insert in the loadedSprites map
    void unloadSprite(vector<pair<pair<int, int>, char>> positions, int id); //utility to insert in the unloadedSprites map
    void removeOldOccurrence(int id, int type);                             //utility to remove the old Sprite occurrence in case a loaded sprite gets unloaded or vice versa
    int checkCollision(int direction, int unit_x, int unit_y);              //tries to move a sprite in the direction provided, return true if it can't be moved due to collision, false otherwise
    bool isOccupied(int x, int y, int self_id);                             //given an x and y position, returns true if that spot is occupied some loaded sprite, false otherwise, ignoring the collision if the spot is occupied by the same sprite that's checking

public:
    Sprite(vector<pair<pair<int, int>, char>> positions);                //constructor
    void deleteSprite();                                                 //deletes a sprite
    int getSpriteID();                                                   //returns sprite identifier
    bool isLoaded();                                                     //returns true if the sprite is inside the loadedSprites vector
    int load();                                                          //pushes a Sprite into the loadedSprites vector, deleting it from the unloadedSprites if needed
    int unload();                                                        //pushes a Sprite into the unloadedSprites vector, deleting it from the loadedSprites if needed
    void setPosition(vector<pair<pair<int, int>, char>> positions);      //sets the position of the aspect inside the canvas
    vector<pair<int, int>> getPosition();                                //returns the positions of the aspect inside the canvas
    static map<int, vector<pair<pair<int, int>, char>>> loadedSprites;   //vector of sprites actually loaded in the canvas
    static map<int, vector<pair<pair<int, int>, char>>> unloadedSprites; //vector of sprites that exist but aren't loaded yet
    static vector<int> unloadedIDs;                                      //vector of identifier that have been unloaded by some sprite, useful to avoid overflow of the spriteID integer TODO PUT ME BACK IN PRIVATE AT THE END
    void setCanvas(vector<vector<char>> canvas);                         //sets the shared canvas that all the sprites will be using
    static vector<vector<char>> getCanvas();                             //returns the canvas
    int move(int direction, int unit_x, int unit_y);                     //moves a sprite, along with his aspect i the canvas,essentially making all his point shift into one of 8 possible directions
};
