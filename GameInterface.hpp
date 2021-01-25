#include <Bonus.hpp>
#include <Enemy.hpp>
#include <Player.hpp>
class GameInterface
{
private:
    //lista bonus sulla mappa
    struct bonuses{
        Bonus b;
        bonuses * next;
    };
    //lista nemici sulla mappa
    struct enemies{
        Enemy e;
        enemies * next;
    };
    typedef enemies* ptr_enemies;
    typedef bonuses* ptr_bonuses;
    Player player; //giocatore

public:

    GameInterface();
    ~GameInterface();
    void checkCollision();
    // void setLevel(level);
    bool checkLevel(int score);
    void setScore(int score);
};
