#include"map.h"
#include<curses.h>

Map::~Map()
{
    if(mapPtr!=nullptr)
        delwin(mapPtr);
}

void Map::DrawMap()
{
    initscr();
    wclear(mapPtr);
    delwin(mapPtr);
    mapPtr = newwin(_mapRow, _mapCol, 0, 0);
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
