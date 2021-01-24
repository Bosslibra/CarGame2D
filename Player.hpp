#include "Entity.hpp"

class Player : public Entity {
   private:
   static const int WIDTH;
   static const int HEIGHT;
    int x, y, width, height;

   public:
    Player(int startX, int startY, int width, int height);
    bool collide(Entity e);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void move(int x, int y, int speed);
};
