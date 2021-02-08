#pragma once
#include <windows.h>
#include <vector>

class LevelInterface {

private:
    int height;
public:
    LevelInterface(int score, int level);

    void drawCanva(int c);
    //aumenta il livello di 1
    void levelUp();
    //diminuisce il livello di 1
    void levelDown();
    //aumenta il punteggio
    void addScore(int bonus);
    //rimuove punteggio
    void subScore(int damage);

};
