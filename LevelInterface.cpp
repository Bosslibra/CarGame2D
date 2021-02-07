#include "LevelInterface.hpp"
#include <windows.h>
#include <iostream>
#include <vector>
int drawCanva(int c, int level, int score){
    int w=c*2;
    char canva[c][w];

    std::string levelChar = "LEVEL: ";
    std::string l = std::to_string(level);
    std::string s = std::to_string(score);
    std::string scoreChar="SCORE: ";
    int countS =0;
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

int levelUp(int level){
    level=level+1;
    return(level);
}
int levelDown(int level){
    level=level-1;
    return(level);
}

int addScore(int score, int bonus){
    score += bonus;
    return(score);
}
int subScore(int score, int damage){
    score-=damage;
    return(score);
}
