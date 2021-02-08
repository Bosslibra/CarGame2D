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
    //aumenta il livello di 1
    void levelUp();
    //diminuisce il livello di 1
    void levelDown();
    //aumenta il punteggio
    void addScore(int bonus);
    //rimuove punteggio
    void subScore(int damage);
    std::vector<std::vector<char>> getCanvas();
};
