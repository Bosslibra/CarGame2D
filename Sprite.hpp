#pragma once
#include <string>
#include <vector>
#include "TextWindow.hpp"
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

   void draw(std::vector <std::vector <char>> &canvas, int x, int y, int width, int height);
};
