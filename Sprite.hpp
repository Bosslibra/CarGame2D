#include <list>
#include <string>

class Sprite
{
private:
    std::list<std::string> sprite;
public:

    Sprite(/* args */);
    ~Sprite();
    void addLine(std::string line);
};
