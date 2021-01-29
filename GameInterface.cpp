#include "GameInterface.hpp"
GameInterface::GameInterface()
{
    this->score = 0;
}

void GameInterface::checkCollision()
{
    ptr_enemies enemy = this->enemies;
    ptr_bonuses bonus = this->bonuses;
    // controllo collisioni con nemici
    while (enemy != nullptr)
    {
        Enemy e = enemy->e;
        if (this->player->collideEnemy(e))
        {
            this->score -= e.getDamage();
        }
    }
    while (bonus != nullptr)
    {
        Bonus b = bonus->b;
        if (this->player->collideBonus(b))
        {
            this->score += b.getBonus();
        }
    }
}
void GameInterface::setScore(int score)
{
    this->score + score;
}
