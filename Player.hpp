#pragma once
#include "Entity.hpp"
#include "Bonus.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"
#include <list>
#include <string>

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
     * @param xMax massima grandezza canvas (x)
     * @param yMax massima grandezza canvas (y)
     * @return true (collide)
     * @return false (non collide)
     */
    bool collideWalls(int xMax, int yMax);
    Sprite getSprite();
};