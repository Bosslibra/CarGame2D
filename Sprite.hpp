#pragma once
#include <list>
#include <string>
#include <vector>
#include "TextWindow.hpp"
class Sprite
{
private:
    std::list<std::string> sprite;

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
    std::list<std::string> getSprite();

    std::vector <std::vector <char>> draw(std::vector <std::vector <char>> canvas, int x, int y, int width, int height);
};
