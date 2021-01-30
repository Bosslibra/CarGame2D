#pragma once
#include <list>
#include <string>
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
    /**
     * @brief
     *
     * @param _textWindow
     */
    void Sprite::draw(int &canvas, int width, int height, int x, int y);
};
