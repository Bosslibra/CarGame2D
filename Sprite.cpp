#include "Sprite.hpp"
#include <list>
#include <string>
Sprite::Sprite(){
}
Sprite::~Sprite(){
}
void Sprite::addLine(std::string line){
    this->sprite.push_back(line);
}

// void Sprite::draw(TextWindow _textWindow){

// }
    std::list<std::string> Sprite::getSprite(){
        return this->sprite;
    }
