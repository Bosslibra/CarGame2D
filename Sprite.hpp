#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <string>

#define X_SPRITE 0
#define Y_SPRITE 1
#define CHAR_SPRITE 2

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

//sprite types
#define ENEMY 18
#define WALL 19
#define PLAYER 20
#define BONUS 21
#define EMPTY -1

//collision type
#define PLAYER_WALL_COLLISION 23
#define PLAYER_ENEMY_COLLISION 24
#define PLAYER_BONUS_COLLISION 26
#define ENEMY_WALL_COLLISION 25
#define ENEMY_BOTTOM_WALL_COLLISION 38
#define BONUS_WALL_COLLISION 28
#define BONUS_ENEMY_COLLISION 30
#define BONUS_BOTTOM_WALL_COLLISION 39
#define ENEMY_OOB 31
#define BONUS_OOB 32
#define PLAYER_OOB 37

//useless data
#define USELESS -2

//actions to be executed after a move
#define UPDATE_SCORE_BONUS 33
#define UPDATE_SCORE_ENEMY 34
#define BOUNCE_ENEMY 35
#define NOTHING 36
#define ERASE 40

using namespace std;

class Sprite
{
private:
    static int canvas_height;                                                  //canvas height, calculated once when a canvas is set, used to check for out of bounds
    static int canvas_width;                                                   //canvas width, calculated once when a canvas is set, used to check for out of bounds
    static vector<vector<char>> canvas;                                        //this class assumes that every sprite is placed in the same canvas, which will always be the case in this project
    static int lastUnusedID;                                                   //last unused identifier
    vector<vector<int>> positions;                                             //vector of vectors, where each y vector is a triple x,y,char
    int spriteID;                                                              //unique identifier
    int type;                                                                  //bonus, enemy, wall or player
    int idGenerator();                                                         //returns an unique identifier, using unloadedIDs if some exists or by advancing lastUnusedID
    int loadSprite();                                                          //utility to insert in the loadedSprites map
    void unloadSprite();                                                       //utility to insert in the unloadedSprites map
    pair<int, int> checkCollision(int direction, int unit_x, int unit_y);      //tries to move a sprite in the direction provided, return true if it can't be moved due to collision, false otherwise
    int isOccupied(int x, int y, int self_id);                                 //given an x and y position, return -1 if the position isn't occupied, otherwise returns the sprite ID of the sprite that occupies that position
    bool isLoaded();                                                           //returns true if the sprite is inside the loadedSprites vector
    pair<int, int> oobCheck(int type);                                         //utility to check for out of bounds collision
    pair<int, int> internalCollisionCheck(int occupied_id, int occupied_type); //utility to check for out of bounds collision
    Sprite getLoadedSprite(int spriteID);

public:
    Sprite();                                                      //empty constructor
    Sprite(vector<vector<int>> positions, int type);               //constructor
    Sprite(vector<vector<int>> positions, int type, int spriteID); //constructor for when I have to load into the map
    static map<int, Sprite> loadedSprites;                         //vector of sprites actually loaded in the canvas
    static vector<int> unloadedIDs;                                //vector of identifier that have been unloaded by some sprite, useful to avoid overflow of the spriteID integer TODO PUT ME BACK IN PRIVATE AT THE END
    static void setCanvas(vector<vector<char>> canvas);            //sets the shared canvas that all the sprites will be using
    static vector<vector<char>> getCanvas();                       //returns the canvas
    static int bottom_wall_id;
    bool isNear(int spriteID);
    int getSpriteID();                                          //returns sprite identifier
    int load();                                                 //pushes a Sprite into the loadedSprites vector, deleting it from the unloadedSprites if needed
    int unload();                                               //pushes a Sprite into the unloadedSprites vector, deleting it from the loadedSprites if needed
    pair<int, int> move(int direction, int unit_x, int unit_y); //moves a sprite, along with his aspect i the canvas,essentially making all his point shift into one of 8 possible directions
};
