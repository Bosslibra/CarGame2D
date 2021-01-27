#include <Bonus.hpp>
#include <Enemy.hpp>
#include <Player.hpp>
class GameInterface
{
private:
    //@param bonuses lista bonus sulla mappa
    struct bonuses{
        Bonus b;
        bonuses * next;
    };
    //@param enemies lista nemici sulla mappa
    struct enemies{
        Enemy e;
        enemies * next;
    };
    //definizione puntatori
    typedef enemies* ptr_enemies;
    typedef bonuses* ptr_bonuses;
    ptr_bonuses bonuses;
    ptr_enemies enemies;

    int score; //@param score score partita

    typedef Player* ptr_player;
    ptr_player player; //giocatore
public:

    GameInterface();
    ~GameInterface();
    void checkCollision();
    // void setLevel(level);
    bool checkLevel(int score);
    void setScore(int score);
};
