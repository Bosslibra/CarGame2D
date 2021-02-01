#include <windows.h>
#include <vector>

class ConsoleDrawing {
private:
    COORD c; 
    std::vector<std::vector<char>> buffer_one;
    std::vector<std::vector<char>> buffer_two;

public:
    ConsoleDrawing();
    BOOL setCursorPosition(int x, int y);
    void Draw();
    void DrawBuffers();
    void setBufferOne(std::vector<std::vector<char>> x);
    void setBufferTwo(std::vector<std::vector<char>> x);
};