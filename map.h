#ifndef _MAP_H
#define _MAP_H
#include "mnode.h"
#include<ncurses.h>
#include<map>
using std::map;
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
        int _nodeWidth = 4;
        int _nodeHeight = 2;
        WINDOW* mapPtr = nullptr;
    public:
        Map() = default;
        Map(int _row, int _col):_mapCol(_col),_mapRow(_row){}
        ~Map();
        map<int, char> NumMap = 
        {
            {0,'0'},{1,'1'},{2,'2'},{3,'3'},{4,'4'},{5,'5'},{6,'6'},{7,'7'},{8,'8'},{9,'9'},
        };
        void FindPath();
        void DrawMap();
        void ClearMap();
};
#endif
