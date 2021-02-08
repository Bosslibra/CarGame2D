#pragma once
#include <string>
#include <list>
#include <vector>
class Sprite
{
private:
    std::vector<std::string> sprite;

public:
    Sprite();
    ~Sprite();
    /**
     * @brief
     *
     * @param line
     */
    void addLine(std::string line);
    /**
     * @brief Get the Sprite object
     *
     * @return std::list<std::string> sprite
     */
    std::vector<std::string> getSprite();
    /**
     * @brief disegna l'entity nel canvas
     *
     * @param canvas canvas su cui apportare le modifiche
     * @param x coordinata x dell'entity
     * @param y coordinata y dell'entity
     * @param width larghezza dell'entity
     * @param height altezza dell'entity
     */
    void draw(std::vector<std::vector<char>> &canvas, int x, int y, int width, int height);
    /**
     * @brief rimuove l'entity dal canvas
     *
     * @param canvas canvas su cui apportare le modifiche
     * @param x coordinata x dell'entity
     * @param y coordinata y dell'entity
     * @param width larghezza dell'entity
     * @param height altezza dell'entity
     */
    void remove(std::vector<std::vector<char>> &canvas, int x, int y, int width, int height);
};
