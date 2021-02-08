#include "ConsoleDrawing.hpp"

ConsoleDrawing::ConsoleDrawing()
{
    this->ShowConsoleCursor(false);
}

//Changes cursor position
BOOL ConsoleDrawing::setCursorPosition(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//hides cursor in console
void ConsoleDrawing::ShowConsoleCursor(bool show)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(out, &cursorInfo);
}

//Draws the game as it starts
void ConsoleDrawing::DrawAtStart(std::vector<std::vector<char>> canvas)
{
    for (int i = 0; i < canvas.size(); i++)
    {
        for (int j = 0; j < canvas[i].size(); j++)
        {
            this->setCursorPosition(i, j);
            std::cout << canvas[i][j];
        }
    }

    this->buffer_one = canvas; //saves copy of vector to later compare it to the updated one, in order to have the lowest calls to std::cout
}

//Draws everything that changed in a given canvas compared to buffer_one
void ConsoleDrawing::DrawBuffer(std::vector<std::vector<char>> canvas)
{
    ConsoleDrawing::ShowConsoleCursor(false);
    //without this check the program crashes the app in case vectors are not of the same size
    if (this->buffer_one.size() == canvas.size() && this->buffer_one[0].size() == canvas[0].size())
    { 
        for (int i = 0; i < canvas.size(); i++)
        {
            for (int j = 0; j < canvas[i].size(); j++)
            {
                if (this->buffer_one[i][j] != canvas[i][j])
                { //only rewrites what has been changed
                    this->setCursorPosition(i, j);
                    std::cout << canvas[i][j];
                }
            }
        }
    }

    this->buffer_one = canvas; //saves copy of vector to later compare it to the updated one, in order to have the lowest calls to std::cout

}
void ConsoleDrawing::drawGameOver(std::vector<std::vector<char>> canvas)
{
    this->ShowConsoleCursor(false);
    system("cls");
    for (int i = 0; i < canvas.size(); i++)
    {
        for (int j = 0; j < canvas[i].size(); j++)
        {
            this->setCursorPosition(j, i);
            std::cout << canvas[i][j];
        }
    }
}