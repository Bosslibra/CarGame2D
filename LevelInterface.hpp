#include <windows.h>
#include <iostream>
#include <vector>

class LevelInterface
{

private:
    int height;
    int width;
    int level;
    int score;
    std::vector<std::vector<char>> canvas;

    void initCanvas();

public:
    LevelInterface(int height);

    void drawCanva(int level, int score);

    std::vector<std::vector<char>> getCanvas();
};
