#include "ConsoleDrawing.cpp"
#include <windows.h>
#include <iostream>
#include <vector>

int main()
{
    ConsoleDrawing c;

    c.setBufferOne({{' '}});
    c.setBufferTwo({{'#', '#', '#', '#'}, {'#', 'A', ' ', '#'}, {'#', ' ', ' ', '#'}, {'#', ' ', ' ', '#'}, {'#', '#', '#', '#'}});

    c.DrawBuffers();
    int z;
    std::cin >> z;
    std::cout << z;
    return 0;
}