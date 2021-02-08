#include <iostream>
using namespace std;

void gameOver(int height){

    if(height<10){
        height=(10-height)+10;
    }
    //salvo come stringhe le righe che compongono la scritta "game Over" 
    std::string gameOver1 = "  __ _  __ _ _ __ ___   ___    _____   _____ _ __  ";
    std::string gameOver2 = " / _` |/ _` | '_ ` _ \\ / _ \\  / _ \\ \\ / / _ \\ '__|";
    std::string gameOver3 ="| (_| | (_| | | | | | |  __/ | (_) \\ V /  __/ |   ";
    std::string gameOver4 = " \\__, |\\__,_|_| |_| |_|\\___|  \\___/ \\_/ \\___|_|   ";
    std::string gameOver5 = "  __/ |                                           ";
    std::string gameOver6= " |___/                                            ";
    std::string ricomincia = "Premi invio per ricominciare";

    //controllori per la lunghezza della stringa più lunga
    int maxGameOver4 = gameOver4.length();

    //setto la larghezza come l'altezza + la scritta più lunga
    int width= height + maxGameOver4;
    
  
    char canva[height][width];
    //iteratore per le stringhe
    int k=0;
    //metto il char # ai margini del riquadro
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(i==0 && j!=0) {
                canva[i][j]='#';
            }  else if(i==height-1) {
                canva[i][j]='#';

            } else {
                canva[i][j]=' ';
            }
            if(j==0){
                canva[i][j]='#';
            }else if(j==width-1) {
                canva[i][j] = '#';
            }
            //inserisco nel riquadro "game over" e istruzioni per ricominciare
            if(j==(width-maxGameOver4)/2+k && i==(height-8)/2 &&  k<maxGameOver4){
               canva[i][j]=gameOver1[k];
                 k++;
            }else if(j==(width-maxGameOver4)/2+k && i==(height-8)/2+1 &&  k<maxGameOver4) {
                canva[i][j]=gameOver2[k];
                k++;
            }else if(j==(width-maxGameOver4)/2+k && i==(height-8)/2+2 &&  k<maxGameOver4) {
                canva[i][j]=gameOver3[k];
                k++;
            }else if(j==(width-maxGameOver4)/2+k && i==(height-8)/2+3 &&  k<maxGameOver4) {
                canva[i][j]=gameOver4[k];
                k++;
            }else if(j==(width-maxGameOver4)/2+k && i==(height-8)/2+4 &&  k<maxGameOver4) {
                canva[i][j]=gameOver5[k];
                k++;
            }else if(j==(width-maxGameOver4)/2+k && i==(height-8)/2+5 &&  k<maxGameOver4) {
                canva[i][j]=gameOver6[k];
                k++;
            }
            else if(j==(width-30)/2+k && i==(height-8)/2+7 &&  k<30) {
                canva[i][j]=ricomincia[k];
                k++;
            }
                std::cout<<canva[i][j];
        }std::cout<<'\n'; k=0;
    }


}



int main() {
    int height = 20;
    gameOver(height);
    return 0;
}
