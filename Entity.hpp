#include <vector>
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
    void setY(int y);
    int getHeight();
    int getWidth();
    bool isOccupied(std::vector<std::vector<char>> canvas);
};