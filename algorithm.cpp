#include "algorithm.h"
#include <curses.h>
#include <iostream>

using std::cout;
using std::endl;

void BFS(Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{
    if(!map.NodeCheck(startNode) || !map.NodeCheck(endNode) || map.Size() <= 0)
    {
        
        endwin();
    }
}

void Dijkstra(const Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{

}

void AStar(const Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{

}
