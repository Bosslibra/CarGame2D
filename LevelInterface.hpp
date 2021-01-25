#include <vector>
using namespace std;
class LevelInterface
{
public:
    LevelInterface();
    void drawEnemies(int numberOfEnemies, vector<vector<char>> canvas);
    void drawBonuses(int numberOfEnemies, vector<vector<char>> canvas);
    void moveCar(char direction, vector<vector<char>> canvas);
    void moveBonus(int x, int y, char direction, vector<vector<char>> canvas);
    void moveEnemy(int x, int y, char direction, vector<vector<char>> canvas);
};