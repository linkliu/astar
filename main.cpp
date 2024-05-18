#include <cstdlib>
#include<iostream>
#include <ncurses.h>
#include<string>
#include<queue>
#include<curses.h>
#include"map.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;

int main(int argc, char* argv[])
{
    Map map(41, 81);
    cout<<"map size="<<map.Size();
    map.DrawMap();
    for (int i = 0; i < map.Size(); i++) 
    {
        auto piPair = map.ExchNumToPosIndex(i);
        map.Draw(i, piPair.first, piPair.second);
    }
    refresh();
    getch();
    map.ClearMap();
    return EXIT_SUCCESS;
}
