#include "Enemy.hpp"
#include "Input.hpp"
#include <list>
#include <vector>
#include <string>
// DIRECTIONS
#define STOPPED 0
#define TOP 1
#define LEFT 2
#define RIGHT 3
#define DOWN 4
#define TOPLEFT 5
#define TOPRIGHT 6
#define DOWNLEFT 7
#define DOWNRIGHT 8
#define ENTER 9
class Player : public Entity
{
private:
    Sprite sprite;

public:
    /**
     * @brief Construct a new Player object
     *
     * @param initialX coordinata x iniziale
     * @param initialY coordinata y iniziale
     * @param width larghezza oggetto
     * @param height altezza oggetto
     */
    Player(int initialX, int initialY, int width, int height);
    ~Player();
    /**
     * @brief Collisioni con nemici
     *
     * @param e  nemico
     * @return true (collide)
     * @return false (non collide)
     */
    bool collideEnemy(Enemy e);
    /**
     * @brief Collisioni con bonus
     *
     * @param b bonus
     * @return true (collide)
     * @return false (non collide)
     */
    bool collideBonus(Bonus b);

    /**
     * @brief controlla le collisioni con i bordi
     *
     * @param width massima grandezza canvas (x)
     * @param height massima grandezza canvas (y)
     * @return true (collide)
     * @return false (non collide)
     */
    void collideWalls(int width, int height);
    /**
     * @brief Get the Sprite object
     *
     * @return Sprite
     */
    Sprite getSprite();
    /**
     * @brief muove il player verso la direzione del tasto premuto
     *
     */
    void move();
    /**
     * @brief disegna il player sul canvas
     *
     * @param canvas canvas di gioco
     */
    void draw(std::vector<std::vector<char>> &canvas);

    /**
     * @brief elimina la vecchia posizione del player dal canvas
     *
     * @param canvas canvas di gioco
     */
    void remove(std::vector<std::vector<char>> &canvas);
};