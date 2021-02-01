#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>
#include <vector>


//This class needs to have a method that draws the map at the start of the game and a method that keeps on drawing 

ConsoleDrawing::ConsoleDrawing(){
    //this initialization of the vector is for testing purposes only and will be deleted before the merge
    this->buffer_one = {{' '}};
    this->buffer_two = {{' '}};
}

void ConsoleDrawing::setBufferOne(std::vector<std::vector<char>> x){
    this->buffer_one = x;
}

void ConsoleDrawing::setBufferTwo(std::vector<std::vector<char>> x){
    this->buffer_two = x;
}

BOOL ConsoleDrawing::setCursorPosition(int x, int y){
    COORD c; 
    c.X = x;
    c.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//Draws the game as it starts
void ConsoleDrawing::DrawAtStart(){
    
    for (int i = 0; i < this->buffer_one.size(); i++){
        for (int j = 0; j < this->buffer_one.size(); j++){
            ConsoleDrawing::setCursorPosition(i, j);
            std::cout << this->buffer_one[i][j];
        }
    }
}

//Draws everything that changed in buffer_two compared to buffer_one
void ConsoleDrawing::DrawBuffers(){
    
    if (this->buffer_one.size() == this->buffer_two.size() && this->buffer_one[0].size() == this->buffer_two[0].size()){ //without this check the program crashes the app in case vectors are not of the same size
        for (int i = 0; i < buffer_two.size(); i++){
            for (int j = 0; j < buffer_two.size(); j++){
                if (this->buffer_one[i][j] != this->buffer_two[i][j]){ //only rewrites what has been changed -> 
                    ConsoleDrawing::setCursorPosition(i, j);
                    std::cout << buffer_two[i][j];
                }
            }
        }
    }
    Sleep(17); //17 milliseconds is equal to 1/60 of a second, so that we can achieve (hopefully) 60fps

}

