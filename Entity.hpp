class Entity
{
protected:
    // @param width e @param height servono per la hitbox
    int x, y, width, height;

public:
    // Classe generale che gestisce metodi comuni a tutte le "entità presenti in gioco"
    Entity(int initialX, int initialY, int width, int height);
    ~Entity();

    int getX();
    int getY();
    int getHeight();
    int getWidth();
    // // void move(char d,int speed);
};