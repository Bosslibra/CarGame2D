#include "Entity.hpp"
// #include "Enemy.hpp"
#include "Sprite.hpp"
#include <vector>
#include <list>
class Bonus : public Entity
{
private:
    int bonus;
    Sprite sprite;

public:
    Bonus(int bonus, int initialX, int initialY, int width, int height);
    ~Bonus();
    /**
     * @brief Get the Bonus object
     *
     * @return int bonus che conferisce l'oggetto
     */
    int getBonus();
    /**
     * @brief muove il bonus
     */
    void move();
    /**
     * @brief disegna il bonus sul canvas
     *
     * @param canvas canvas del gioco da modificare
     */
    void draw(std::vector<std::vector<char>> &canvas);
    /**
     * @brief rimuove la vecchia posizione del bonus
     *
     * @param canvas canvas del gioco da modificare
     */
    void remove(std::vector<std::vector<char>> &canvas);
    /**
     * @brief controlla se collide con il bordo inferiore (se collide va cancellato)
     *
     * @param screenHeight grandezza schermo
     * @param borderWidth larghezza bordo
     * @return true collide
     * @return false non collide
     */
    bool collideBottomWall(int screenHeight, int borderWidth);
};
