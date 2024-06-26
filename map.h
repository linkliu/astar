#ifndef _MAP_H
#define _MAP_H
#include "mnode.h"
#include<map>
#include <utility>
#include<list>
using std::map;
using std::list;
using std::pair;

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
        map<int, MNode> nodeMap;
        bool isMapIndexValid(int my, int mx)const;
        bool isNumValid(int num) const;
        void filterNeightbor(pair<int, int>  &npair, list<MNode> &nlist);
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
        void Draw(const char*, int _mapIndex_Y, int _mapIndex_X);
        void Draw(const MNode& node)const;
        void Draw(const list<MNode> & dlist) const;
        int Size() const;
        int GetCol(){return _mapCol;}
        int GetRow(){return _mapRow;}
        const MNode& GetNode(int _mapIndex_Y, int _mapIndex_X) const;
        pair<int, int> ExchNumToMapIndex(int num) const;
        pair<int, int> ExchMapIndexToPOS(int _mapIndex_Y, int _mapIndex_X) const;
        int ExchMapIndexToNum(int _mapIndex_Y, int _mapIndex_X) const;
        list<MNode>& GetNeighbors(const MNode& node, list<MNode>& neighborsList);
        bool NodeCheck(const MNode& node);
};
#endif
