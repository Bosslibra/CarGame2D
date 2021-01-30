#include <windows.h>

class ConsoleDrawing {
private:
    COORD c; 
public:
    BOOL setCursorPosition(int x, int y);
};