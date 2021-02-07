#pragma once
#include <windows.h>
#include <vector>
class LevelInterface {

private:
    int c;
    int score;
    int level;
    int bonus;
    int damage;
public:
    //costruttore
    LevelInterface();
    //prende una coordinata c e disegna l'interfaccia di level e score
    drawCanva(int c);
    //ritorna il livello aumentato di 1
    levelUp(int level);
    //ritorna il livello diminuito di 1
    levelDown(int level);
    //ritorna punteggio aumentato di bonus
    addScore(int score, int bonus);
    //ritorna punteggio sottratto di danno
    subScore(int score, int damage);
};