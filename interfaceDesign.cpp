#include <iostream>
using namespace std;

const int HEIGHT = 27; 
const int WIDTH = 48*2; // 48*2 per normalizzare la grandezza dell'array quando viene stampato
const int VLINE = (WIDTH *3)/4; //divido lo schermo in due parti, a sinistra (tre quarti dello schermo) sarà dove 
// si gioca, a destra saranno scritti Punteggio e Livello
const int XCOORDTEXT = VLINE + ((WIDTH - VLINE)/2) -3 ;
//Trovo il centro tra il lato destro e VLINE, gli tolgo tre (sia la scritta "SCORE:" che "LEVEL:" hanno sei caratteri)
// e sommo al tutto VLINE, in modo da trovare dove iniziare a scrivere SCORE e LEVEL per averli centrati

int main(){

    char mymap[WIDTH][HEIGHT];

    //drawing hastags on borders
    for (int x = 0; x < WIDTH-1; x++){
        for (int y = 0; y < HEIGHT; y++){
            if (x == 0 || x == WIDTH-2 || x == (VLINE-1)){
                mymap [x][y] = '#';
            } else if (y == 0 || y == HEIGHT-1){
                if ((x%2) == 0 && (y == 0 || y == HEIGHT -1)){
                    mymap [x][y] = '#';
                } else {
                    mymap [x][y] = ' ';
                }
            } else {
                mymap [x][y] = ' '; // se togli questo l'array non è inizializzato e crasha tutto
            }
        }
    }

    //Scrivere "SCORE:"
    mymap [XCOORDTEXT  ][5] = 'S';
    mymap [XCOORDTEXT+1][5] = 'C';
    mymap [XCOORDTEXT+2][5] = 'O';
    mymap [XCOORDTEXT+3][5] = 'R';
    mymap [XCOORDTEXT+4][5] = 'E';
    mymap [XCOORDTEXT+5][5] = ':';

    mymap [XCOORDTEXT+5][5+2] = '9';

    //Scrivere "LEVEL:"
    mymap [XCOORDTEXT  ][9] = 'L';
    mymap [XCOORDTEXT+1][9] = 'E';
    mymap [XCOORDTEXT+2][9] = 'V';
    mymap [XCOORDTEXT+3][9] = 'E';
    mymap [XCOORDTEXT+4][9] = 'L';
    mymap [XCOORDTEXT+5][9] = ':';
    
    mymap [XCOORDTEXT+5][9+2] = '9';

    //per testing (stampa l'array)
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH-1; x++){
            cout << mymap[x][y];
        }
        cout << endl;
    }
}