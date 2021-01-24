class Entity
{
private:
    /* data */
public:
    Entity(int initialX, int initialY, int width, int height);
    ~Entity();

    bool collide(Entity e);
    int getX();
    int getY();
    int getHeight();
    int getWidth();
    void move(int x, int y,int speed);
};