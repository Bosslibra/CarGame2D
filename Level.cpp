#include "Level.hpp"


Level::Level(int enemySpawnRate, int bonusSpawnRate, int maxScore, int minScore){
    this->player = new Player(0,0,3,3); //posizioni player
    this->score = minScore;
}