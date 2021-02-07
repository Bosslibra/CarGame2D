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