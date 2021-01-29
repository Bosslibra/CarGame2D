#include <list>
#include <string>
#include <TextWindow.hpp>

class Sprite
{
private:
    std::list<std::string> sprite;
public:

    Sprite();
    ~Sprite();
    /**
     * @brief
     *
     * @param line
     */
    void addLine(std::string line);
};

void draw(TextWindow _textWindow);