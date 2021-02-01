#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>
#include <vector>


//This class needs to have a method that draws the map at the start of the game and a method that keeps on drawing 

ConsoleDrawing::ConsoleDrawing(){
    //this initialization of the vector is for testing purposes only and will be deleted before the merge
    this->buffer_one = {};
    this->buffer_two = {};
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

void ConsoleDrawing::Draw(){
    
    for (int i = 0; i < this->buffer_one.size(); i++){
        for (int j = 0; j < this->buffer_one.size(); j++){
            ConsoleDrawing::setCursorPosition(i, j);
            std::cout << this->buffer_one[i][j];
        }
    }
    /*ConsoleDrawing::DrawBuffers(this->buffer_two, this->buffer_one);

    std::vector<std::vector<char>> temp = this->buffer_one;
    this->buffer_one = this->buffer_two;
    this->buffer_two = temp;*/
}

void ConsoleDrawing::DrawBuffers(){

    //do I need to change this before the merge??
    for (int i = 0; i < buffer_two.size(); i++){
        for (int j = 0; j < buffer_two.size(); j++){
            if (this->buffer_one[i][j] != this->buffer_two[i][j]){ //only rewrites what has been changed
                ConsoleDrawing::setCursorPosition(i, j);
                std::cout << buffer_two[i][j];
            }
        }
    }

    //the next three lines are only for testing purposes only and will be deleted before the merge !!!!
    std::vector<std::vector<char>> temp = this->buffer_one;
    this->buffer_one = this->buffer_two;
    this->buffer_two = temp;

    Sleep(17); //17 milliseconds is equal to 1/60 of a second, so that we can achieve (hopefully) 60fps

}

