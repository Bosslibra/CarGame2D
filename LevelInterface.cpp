#include "LevelInterface.hpp"
#include <windows.h>
#include <iostream>
#include <vector>

LevelInterface(){}

void LevelInterface::drawCanva(int c){
    int w=c*2;
    char canva[c][w];

    std::string levelChar = "LEVEL: ";
    std::string l = std::to_string(this->level);
    std::string s = std::to_string(this->score);
    std::string scoreChar = "SCORE: ";
    int countS = 0;
    int maxS = s.length() + scoreChar.length();
    int countL = 0;
    int maxL = l.length() + levelChar.length();
    int k=0;
    int lv=0;

    scoreChar+=s;
    levelChar+=l;
    for(int i=0; i<c; i++){
        for(int j=0; j<w; j++){

            if(i==0 && j!=0) {
                canva[i][j]='-';
            }  else if(i==c-1) {
                canva[i][j]='_';

            } else {
                canva[i][j]=' ';
            };
            if(j==0){
                canva[i][j]='|';
            }else if ((j==(w/10)+countS) && i==(c/4) && countS<maxS){
                canva[i][j]=scoreChar[k];

                countS++;
                k++;
            } else if ((j==(w/10)+ countL && i==(c/4)+2 && countL<maxL)){
                canva[i][j]=levelChar[lv];
                countL++;
                lv++;
            } else if(j==w-1){
                canva[i][j]='|';
            }

            std::cout<<canva[i][j];

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
