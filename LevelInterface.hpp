#include <vector>
class LevelInterface
{
public:
    void drawEnemies(int numberOfEnemies, std::vector<std::vector<char>> canvas);
    void drawBonuses(int numberOfEnemies, std::vector<std::vector<char>> canvas);
    void moveCar(char direction, std::vector<std::vector<char>> canvas);
    void moveBonus(int x, int y, char direction, std::vector<std::vector<char>> canvas);
    void moveEnemy(int x, int y, char direction, std::vector<std::vector<char>> canvas);
};