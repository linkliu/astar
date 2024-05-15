#ifndef _MAP_H
#define _MAP_H
#include "mnode.h"
#include<ncurses.h>
enum class ENodeState
{
    UNCHECK,
    CHECKED
};
class Map
{
    private:
        int _mapCol = 20;
        int _mapRow = 20;
        int _colWidth = 4;
        int _rowHeight = 2;
        WINDOW* mapPtr = nullptr;
    public:
        Map() = default;
        Map(int _row, int _col):_mapCol(_col),_mapRow(_row){}
        ~Map();
        void FindPath();
        void DrawMap();
        void ClearMap();
};
#endif
