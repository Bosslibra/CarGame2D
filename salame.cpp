#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;

class snake
{
private:
    int x, y, tail, apple_x, apple_y, dx, dy, lastpos_x, lastpos_y, points, level;
    bool go, eaten;
    char **map;

    //vectors to store the tail of the snake

    std::vector<int> x_tail;
    std::vector<int> y_tail;

public:
    snake();
    ~snake();
    void start_game();
    void game_over();
    void move();
    void input();
    void apple();
    void game();
    void refresh();
    void clear();
    void draw();
    void hidecursor();
    void test();
    int check_over();
};

//hide cursor function

void snake::hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//test function

void snake::test()
{
    for (int i = 0; i <= 5; i++)
    {
        x_tail.push_back(i);
    }
    cout << endl;
    x_tail.insert(x_tail.begin(), 100);
    for (unsigned i = 0; i < x_tail.size(); i++)
    {
        cout << x_tail[i] << " ";
    }
}

//initial values

snake::snake()
{
    go = true;
    eaten = false;
    level = 100;
    dx = 0;
    dy = 1;
    x = 6;
    y = 25;
    apple_x = 1;
    apple_y = 1;
    tail = 3;
    points = 0;
}

snake::~snake()
{
    for (int i = 0; i < 26; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}

//start the game

void snake::start_game()
{
    hidecursor();
    map = new char *[26];
    for (int i = 0; i < 26; i++)
    {
        map[i] = new char[81];
    }
    draw();
}

//draw map

void snake::draw()
{

    //draw top and bottom walls

    for (int j = 1; j <= 80; j++)
    {
        map[1][j] = char(178);
        map[25][j] = char(178);
    }

    //draw right and left walls

    for (int i = 1; i <= 25; i++)
    {
        map[i][1] = char(178);
        map[i][80] = char(178);
    }
    for (int i = 2; i <= 24; i++)
    {
        for (int j = 2; j <= 79; j++)
        {
            map[i][j] = ' ';
        }
    }
    //draw head and tail of the snake

    map[x][y] = char(254);
    for (int i = 22; i <= 24; i++)
    {
        y_tail.push_back(i);
    }
    for (int i = 0; i < tail; i++)
    {
        x_tail.push_back(x);
    }
    for (int i = 0; i < tail; i++)
    {
        map[x_tail[i]][y_tail[i]] = 'o';
    }

    //display the entire map

    for (int i = 1; i <= 25; i++)
    {
        for (int j = 1; j <= 80; j++)
        {
            if (j == 40)
                cout << map[i][j] << endl;
            else
                cout << map[i][j];
        }
    }

    //generate apple
    apple();

    //movement
    move();
}

void snake::refresh()
{

    //update map with the new positions

    map[x][y] = char(254);
    for (int i = 0; i < tail; i++)
    {
        map[x_tail[i]][y_tail[i]] = 'o';
    }

    //display the updated map

    for (int i = 1; i <= 25; i++)
    {
        for (int j = 1; j <= 80; j++)
        {
            if (j == 80)
                cout << map[i][j] << endl;
            else
                cout << map[i][j];
        }
    }

    //continue to detect movement after update
    move();
}

//apple random generation
void snake::apple()
{
    srand((unsigned)time(NULL));
    apple_x = 2 + rand() % (24 - 2 + 1);
    apple_y = 2 + rand() % (79 - 2 + 1);
    map[apple_x][apple_y] = 'o';
}

//check if the snake hit a wall or himself

int snake::check_over()
{
    if ((x == 1) || (x == 25) || (y == 1) || (y == 80))
    {
        return 1;
    }
    for (int i = 0; i < tail - 1; i++)
    {
        if ((x_tail[i] == x) && (y_tail[i] == y))
            return 1;
    }
    return 0;
}

//game over...

void snake::game_over()
{
    system("cls");
    Sleep(1000);
    cout << "Game Over!!!" << endl;
    Sleep(50);
    cout << "You earned " << points << " points!!!" << endl;
}

void snake::clear()
{
    system("cls");
}

//snake movement

void snake::move()
{

    //repeat movement until game over
    while (go == true)
    {

        //update directions of the snake if a key is pressed... if not keep previous directions

        if (_kbhit())
        {
            input();
        }
        //update head position

        cout << endl;
        lastpos_x = x;
        lastpos_y = y;
        x = x + dx;
        y = y + dy;

        //generate new apple and increase tail if apple is eaten
        if ((x == apple_x) && (y == apple_y))
        {
            points = points + 10;
            eaten = true;
            map[apple_x][apple_y] = ' ';
            apple();
        }

        if (eaten == true)
        {
            tail++;
            x_tail.insert(x_tail.begin(), x_tail[0]);
            y_tail.insert(y_tail.begin(), y_tail[0]);
            eaten = false;
        }

        //build tail

        map[x_tail[0]][y_tail[0]] = ' ';
        for (int i = 0; i < tail - 1; i++)
        {
            x_tail[i] = x_tail[i + 1];
            y_tail[i] = y_tail[i + 1];
        }
        x_tail[tail - 1] = lastpos_x;
        y_tail[tail - 1] = lastpos_y;
        if (check_over())
        {
            game_over();
            go = false;
            break;
        }

        //increase velocity depending on the points earned

        if (points > 50 && points <= 100)
        {
            level = 75;
        }
        else if (points > 100 && points <= 150)
        {
            level = 50;
        }
        else if (points > 150)
        {
            level = 25;
        }
        Sleep(level);

        //clear the screen and update the map

        clear();
        refresh();
    }
}

//keyboard input

void snake::input()
{
    if (_kbhit())
    {
        char in = _getch();
        switch (in)
        {
        case 'd':
        {
            dx = 0;
            dy = 1;
            break;
        }
        case 'w':
        {
            dx = -1;
            dy = 0;
            break;
        }
        case 'a':
        {
            dx = 0;
            dy = -1;
            break;
        }
        case 's':
        {
            dx = 1;
            dy = 0;
            break;
        }
        }
    }
}

int main()
{
    snake game;
    game.start_game();
    system("pause");
    return 0;
}