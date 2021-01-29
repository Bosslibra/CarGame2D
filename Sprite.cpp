#include "Sprite.hpp"
#pragma once
int x, y;
Sprite::Sprite(){
}
void Sprite::addLine(std::string line){
    this->sprite.push_back(line);
}

// void Sprite::draw(TextWindow _textWindow){

// }
    std::list<std::string> Sprite::getSprite(){
        return this->sprite;
    }
