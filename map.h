#ifndef _MAP_H
#define _MAP_H
#include "mnode.h"
#include<ncurses.h>
#include<map>
#include <utility>
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
        int _maxMapIndex_y = 0;
        int _maxMapIndex_X = 0;
        WINDOW* mapPtr = nullptr;
        bool isMapIndexValid(int my, int mx);
    public:
        Map() = default;
        Map(int _row, int _col);
        ~Map();
        map<int, char> NumMap = 
        {
            {0,'0'},{1,'1'},{2,'2'},{3,'3'},{4,'4'},{5,'5'},{6,'6'},{7,'7'},{8,'8'},{9,'9'},
        };
        void FindPath();
        void DrawMap();
        void ClearMap();
        void Draw(int num, int _mapIndex_Y, int _mapIndex_X);
        void Draw(char ch, int _mapIndex_Y, int _mapIndex_X);
        int Size();
        int GetCol(){return _mapCol;}
        int GetRow(){return _mapRow;}
        std::pair<int, int> ExchNumToPosIndex(int num);
        
};
#endif
