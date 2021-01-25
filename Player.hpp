#include <Entity.hpp>
#include <Bonus.hpp>
#include <Enemy.hpp>
class Player : public Entity
{
private:
    /* data */
public:
    Player(int initialX, int initialY, int width, int height);
    ~Player();
    bool collide(Entity e);
};