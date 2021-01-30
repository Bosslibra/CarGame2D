#pragma once
#include <list>
#include <string>
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
    std::list<std::string> getSprite();
};

// void draw(TextWindow _textWindow);