#include "ConsoleDrawing.hpp"
#include <windows.h>
#include <iostream>
#include <vector>


ConsoleDrawing::ConsoleDrawing(){
    this->buffer_one = {{'#', '#', '#', '#'}, {'#', ' ', ' ', '#'}, {'#', 'A', ' ', '#'}, {'#', ' ', ' ', '#'},{'#', '#', '#','#'}};
    this->buffer_two = {{'#', '#', '#', '#'}, {'#', 'A', ' ', '#'}, {'#', ' ', ' ', '#'}, {'#', ' ', ' ', '#'},{'#', '#', '#','#'}};
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


    for (int i = 0; i < buffer_two.size(); i++){
        for (int j = 0; j < buffer_two.size(); j++){
            if (this->buffer_one[i][j] != this->buffer_two[i][j]){ //only rewrites what has been changed
                ConsoleDrawing::setCursorPosition(i, j);
                std::cout << buffer_two[i][j];
            }
        }
    }
    std::vector<std::vector<char>> temp = this->buffer_one;
    this->buffer_one = this->buffer_two;
    this->buffer_two = temp;

    Sleep(17);

}