#include <Player.hpp>
class Level
{
private:
    int score;
    Player* player; //giocatore
public:
    /**
     * @brief Construct a new Level object
     *
     * @param enemySpawnRate numero di nemici che spawnano ogni ciclo
     * @param bonusSpawnRate numero di bonus che spawnano ogni ciclo
     * @param maxScore max score per level up
     * @param minScore minimo score per essere nel livello
     */
    Level(int enemySpawnRate, int bonusSpawnRate, int maxScore, int minScore);
    ~Level();
    void setScore();
    int getScore();
    int getEnemySpawnRate();
    int getBonusSpawnRate();
};
