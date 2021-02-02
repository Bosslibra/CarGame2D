#include <windows.h>
#include <vector>

class ConsoleDrawing {
private:
    COORD c; 
    std::vector<std::vector<char>> buffer_one;
public:
    ConsoleDrawing();
    BOOL setCursorPosition(int x, int y);
    void DrawAtStart(std::vector<std::vector<char>> canvas);
    void DrawBuffer(std::vector<std::vector<char>> canvas);
};