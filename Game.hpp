#include "ConsoleDrawing.hpp"
#include "Player.hpp"
#include <vector>
class Game
{
private:
    ConsoleDrawing console;
    const int width = 40;
    const int height = 50;
    int speed;
    std::vector<std::vector<char>> canvas;

    //@param bonuses lista bonus sulla mappa
    std::vector<Bonus> bonuses;
    //@param bonuses lista nemici sulla mappa
    std::vector<Enemy> enemies;
    //danno e bonus inflitti
    int damage;
    int bonus;


    int score; //@param score score partita

    Player *player; //giocatore
    //numero bonus nella mappa
    int nEnemy;
    int nBonus;

    int levelUpTarget;
    int prevLevel;
public:
    Game();
    ~Game();
    void run();
    void checkCollision();
    void move();
    void draw();
    void checkLevel();
    void setScore(int score);
    void resetCanvas();
    void addEnemy(int damage);
    void addBonus(int bonus);
};
