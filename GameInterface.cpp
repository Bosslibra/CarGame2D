#include <GameInterface.hpp>

void GameInterface::checkCollision(){
        ptr_enemies enemy = this->enemies;
        ptr_bonuses bonus = this->bonuses;
        ptr_player player = this->player;
    // controllo collisioni con nemici
    while (enemy -> next != nullptr){
        Enemy e = enemy->e;
        if (player->collideEnemy(e)){
            this->score -= e.getDamage();
        }
    }
    while (bonus -> next != nullptr){
        Bonus b = bonus->b;
        if (player->collideBonus(b)){
            this->score += b.getBonus();
        }
    }

}
