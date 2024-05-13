#ifndef _MAP_H
#define _MAP_H
#include "mnode.h"
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
    public:
        Map() = default;
        Map(int _col, int _row):_mapCol(_col),_mapRow(_row){}
        void Init();
        void FindPath();
};
#endif
