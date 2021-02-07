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

   void draw(std::vector <std::vector <char>> &canvas, int x, int y, int width, int height);
   void remove(std::vector<std::vector<char>> &canvas, int x, int y, int width, int height);
};
