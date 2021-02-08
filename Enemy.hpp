#include "Sprite.hpp"
#include "Bonus.hpp"
#include <ctime>
#include <vector>

class Enemy : public Entity
{
private:
    int damage = 200;
    int yDirection;
    Sprite sprite;

public:
    Enemy(int damage, int initialX, int initialY, int width, int height);
    ~Enemy();
    /**
     * @brief Get the Damage object
     *
     * @return int danno che causa il nemico
     */
    int getDamage();
    /**
     * @brief muove il nemico
     *
     * @param screenWidth larghezza schermo possibile
     * @param borderWidth larghezza bordo dello schermo (# disegnato)
     */
    void move(int screenWidth, int borderWidth);
    /**
     * @brief disegna il nemico sul canvas
     *
     * @param canvas canvas del gioco
     */
    void draw(std::vector<std::vector<char>> &canvas);
    /**
     * @brief cancella la vecchia posizione del player dal canvas
     *
     * @param canvas canvas del gioco
     */
    void remove(std::vector<std::vector<char>> &canvas);
    /**
     * @brief verifica che non collida contro i bordi laterali
     *
     * @param screenWidth larghezza bordo
     * @param borderWidth dimensione del bordo (# disegnato)
     */
    void collideLateralWalls(int screenWidth, int borderWidth);
    /**
     * @brief controlla se collide con il bordo inferiore (se collide va cancellato)
     *
     * @param screenHeight grandezza schermo
     * @param borderWidth larghezza bordo
     * @return true collide
     * @return false non collide
     */
    bool collideBottomWall(int screenHeight, int borderWidth);
    /**
     * @brief controlla che non collida contro un bonus
     *
     * @param bonuses lista dei bonus presenti nella mappa
     */
    void collideBonus(std::vector<Bonus> bonuses);
    /**
     * @brief controlla che non collida contro un nemico
     *
     * @param enemies lista dei bonus presenti nella mappa
     */
    void collideEnemy(std::vector<Enemy> enemies);
};