#include"map.h"
#include<curses.h>

Map::~Map()
{
    if(mapPtr!=nullptr)
        delwin(mapPtr);
}

void Map::DrawMap(int col, int row)
{
    initscr();
    wclear(mapPtr);
    delwin(mapPtr);
    mapPtr = newwin(50, 100, 0, 0);
    box(mapPtr, 0, 0);
    wrefresh(mapPtr);
    wgetch(mapPtr);
    this->ClearMap();
}

void Map::ClearMap()
{
    delwin(mapPtr);
    mapPtr = nullptr;
    endwin();
}
