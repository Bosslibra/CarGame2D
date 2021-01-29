// #include "GameInterface.hpp"
// #include "Player.hpp"
#include <iostream>
#include <list>
#include <string>
#include "Sprite.hpp"

int main(){
    // GameInterface g();
    // Player p(0,0,3,3);
    // p.getSprite();
    Sprite s;
    s.addLine("ciao");
    s.addLine("we");
    s.addLine("i");
    std::list<std::string> sprite = s.getSprite();
    for (auto v : sprite){
        std::cout << v;
    }
    return 0;
}