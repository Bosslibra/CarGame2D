#include "LevelInterface.hpp"

LevelInterface::LevelInterface()
{}
LevelInterface::~LevelInterface() {}
void LevelInterface::initCanvas()
{
    this->width = 40; //larghezza fissa
    //cicli per la costruzione della cornice e degli spazi bianchi interni
    for (int i = 0; i < this->height; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < this->width; j++)
        {
            if (j == this->width - 1 || i == this->height - 1 || j == 0)
            {
                row.push_back('#');
            }
            else if (i == 0)
            {
                row.push_back('|');
            }
            else
            {
                row.push_back(' ');
            }
        }
        this->canvas.push_back(row);
    }
}
void LevelInterface::drawCanva(int level, int score)
{
    this->initCanvas();
    //salvo come stringhe il valore di "level" e "score"
    std::string levelString = "LEVEL: " + std::to_string(level);
    std::string scoreString = "SCORE: " + std::to_string(score);

    // mi posiziono a metà schermo -1
    int yMid = this->width / 2;
    for (int i = 0; i < scoreString.length(); i++)
    {
        //controllo che non vada in overflow la scritta
        if (i < canvas[yMid].size())
        {
            canvas[i + 10][yMid] = scoreString.at(i);
        }
    }
    yMid += 2; //lascio uno spazio bianco tra le scritte
    for (int i = 0; i < levelString.length(); i++)
    {
        //controllo che non vada in overflow la scritta
        if (i < canvas[yMid].size())
        {
            canvas[i + 10][yMid] = levelString.at(i);
        }
    }
}

std::vector<std::vector<char>> LevelInterface::getCanvas()
{
    return this->canvas;
}
void LevelInterface::setHeight(int height) { this->height = height; }
