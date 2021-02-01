#include "Bonus.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include <vector>
class GameInterface
{
private:
    const int width = 100;
    const int height = 100;
    std::vector<std::vector<char>> canvas;

    //@param bonuses lista bonus sulla mappa
    struct bonuses
    {
        Bonus b;
        bonuses *next;
    };

    //@param enemies lista nemici sulla mappa
    struct enemies
    {
        Enemy e;
        enemies *next;
    };
    //definizione puntatori
    typedef enemies *ptr_enemies;
    typedef bonuses *ptr_bonuses;
    ptr_bonuses bonuses;
    ptr_enemies enemies;

    int score; //@param score score partita

    Player *player; //giocatore
public:
    GameInterface();
    ~GameInterface();
    void run();
    void checkCollision();
    // void setLevel(level);
    bool checkLevel();
    void setScore(int score);
    void resetCanvas();
};
