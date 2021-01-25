//this is a file used for testing purposes

#include "Sprite.cpp"
#include <iostream>
using namespace std;
void printUnloaded()
{
    cout << "UNLOADED" << endl;
    cout << "ID\tX\tY" << endl;
    for (map<int, vector<int>>::iterator it = Sprite::unloadedSprites.begin(); it != Sprite::unloadedSprites.end(); it++)
    {
        cout << it->first << "\t" << it->second[0] << "\t" << it->second[1] << endl;
    }
    cout << endl;
}

void printLoaded()
{
    cout << "LOADED" << endl;
    cout << "ID\tX\tY" << endl;
    for (map<int, vector<int>>::iterator it = Sprite::loadedSprites.begin(); it != Sprite::loadedSprites.end(); it++)
    {
        cout << it->first << "\t" << it->second[0] << "\t" << it->second[1] << endl;
    }
    cout << endl;
}

void printUnloadedIDs()
{
    cout << "UNLOADED IDS" << endl;
    cout << "ID" << endl;
    for (auto s : Sprite::unloadedIDs)
    {
        cout << s << endl;
    }
    cout << endl;
}

int main()
{
    Sprite test(1, 2);
    Sprite test2(2, 3);
    Sprite test3(3, 4);
    printUnloaded();
    printUnloadedIDs();
    cout << "Loading every Sprite" << endl;
    test.load();
    test2.load();
    test3.load();
    printLoaded();
    printUnloaded();
    cout << "Deleting every Sprite" << endl;
    test.deleteSprite();
    test2.deleteSprite();
    test3.deleteSprite();
    printUnloaded();
    printLoaded();
    printUnloadedIDs();
}