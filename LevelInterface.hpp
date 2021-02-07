#include "LevelInterface.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

LevelInterface(){}

void LevelInterface::drawCanva(){
    int width=height*2;
    //la dimensione dell'interfaccia è data dall'altezza presa dalla classe
    //e la larghezza composta moltiplicato l'altezza per due
    char canva[height][width];

    //salvo come stringhe le parole "level" e "score"
    std::string levelString = "LEVEL: ";
    std::string scoreString = "SCORE: ";
    //salvo come stringhe i parametri level e score, che sarebbero interi
    std::string actualLevel = std::to_string(this->level);
    std::string actualString = std::to_string(this->score);
    //controllori per la lunghezza delle stringhe
    int countScoreChar = 0;
    int maxScoreChar = actualString.length() + scoreString.length();
    int countLevelChar = 0;
    int maxLevelChar = actualLevel.length() + levelString.length();
    //controllori
    int k=0;
    int lv=0;

    //la stringa del punteggio e del livello viene concatenata all'effettivo
    //punteggio e livello
    scoreString+=actualString;
    levelString+=actualLevel;

    //cicli per la costruzione della cornice, degli spazi bianchi interni
    //e per l'inserimento delle scritte score e level
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){

            if(i==0 && j!=0) {
                canva[i][j]='-';
            }  else if(i==height-1) {
                canva[i][j]='_';

            } else {
                canva[i][j]=' ';
            };
            if(j==0){
                canva[i][j]='|';
            }else if ((j==(width/10)+countScoreChar) && i==(width/4) && countScoreChar<maxScoreChar){
                canva[i][j]=scoreString[k];

                countStringChar++;
                k++;
            } else if ((j==(width/10)+ countLevelChar && i==(heihgt/4)+2 && countLevelChar<maxLevelChar)){
                canva[i][j]=levelString[lv];
                countLevelChar++;
                lv++;
            } else if(j==width-1){
                canva[i][j]='|';
            }

        }std::cout<<'\n';
    }
}

void LevelInterface::levelUp(){
    this->level += 1;

}
void LevelInterface::levelDown(){
    this->level -= 1;
}

void LevelInterface::addScore(int bonus){
    this->score += bonus;
}

void LevelInferface::subScore(int damage){
    this->score -= damage;
}
