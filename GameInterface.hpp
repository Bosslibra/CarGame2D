#include "ConsoleDrawing.hpp"
#include "Bonus.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <vector>
class GameInterface
{
private:
    ConsoleDrawing console;
    const int width = 20;
    const int height = 30;
    int speed;
    std::vector<std::vector<char>> canvas;

    //@param bonuses lista bonus sulla mappa
    std::list<Bonus> bonuses;
    //@param bonuses lista nemici sulla mappa
    std::list<Enemy> enemies;
    //danno e bonus inflitti
    int damage;
    int bonus;


    int score; //@param score score partita

    Player *player; //giocatore
    //numero bonus nella mappa
    int nEnemy;
    int nBonus;

    int levelUpTarget;
public:
    GameInterface();
    ~GameInterface();
    void run();
    void checkCollision();
    void move(int direction);
    void draw();
    // void setLevel(level);
    void checkLevel();
    void setScore(int score);
    void resetCanvas();
    // void spawnEntities();
    void addEnemy(int damage);
    void addBonus(int bonus);
};
