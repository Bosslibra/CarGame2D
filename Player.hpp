#include <Entity.hpp>
#include <Bonus.hpp>
#include <Enemy.hpp>
class Player : public Entity
{
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
};