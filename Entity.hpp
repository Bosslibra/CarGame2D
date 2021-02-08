#include <vector>
class Entity
{
protected:
    // @param width serve per la hitbox
    // @param height serve per la hitbox
    int x, y, width, height;

public:
    // Classe generale che gestisce metodi comuni a tutte le "entità presenti in gioco"
    Entity(int initialX, int initialY, int width, int height);
    ~Entity();
    /**
     * @brief restituisce la coordinata x dell'entità
     *
     * @return int xcoord
     */
    int getX();
    /**
     * @brief restituisce la coordinata y dell'entità
     *
     * @return int ycoord
     */
    int getY();
    /**
     * @brief imposta la coordinata y dell'entità a un valore preciso
     *
     * @param y nuova y dell'entità
     */
    void setY(int y);
    /**
     * @brief Get the Height object
     *
     * @return int
     */
    int getHeight();
    /**
     * @brief Get the Width object
     *
     * @return int
     */
    int getWidth();
    /**
     * @brief verifica che l'area in cui doeve spawnare l'entità non sia occupata
     *
     * @param canvas canvas di gioco
     * @return true
     * @return false
     */
    bool isOccupied(std::vector<std::vector<char>> canvas);
};