#include <Entity.hpp>
class Enemy : public Entity
{
private:
    int damage = 200;
public:
    Enemy(int damage,int initialX, int initialY, int width, int height);
    ~Enemy();
    int getDamage();
};
