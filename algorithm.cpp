#include "algorithm.h"
#include "mnode.h"
#include <algorithm>
#include <curses.h>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::find_if;

void BFS(Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{
    if(!map.NodeCheck(startNode) || !map.NodeCheck(endNode) || map.Size() <= 0)
    {
        stringstream ss;
        ss<<"invalid start node:"<<startNode.ToString()<<" or end node:"<<endNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return;
    }
    list<MNode> ckList;
    ckList.push_back(startNode);
    vector<MNode>  stepedVec;
    stepedVec.push_back(startNode);
    list<MNode> nbList;
    while(!ckList.empty())
    {
        MNode ckNode = ckList.front();
        for ( MNode nextNode: map.GetNeighbors(ckNode, nbList)) 
        {
            //如果还没有检查过，插入到下一个要找的步骤
            auto checkedFun = [nextNode](MNode node){return node.IsSamePos(nextNode); };
            if(find_if(stepedVec.cbegin(), stepedVec.cend(), checkedFun) == stepedVec.cend())
            {
                ckList.push_back(nextNode);
                stepedVec.push_back(nextNode);
            }
            //TODO 如果找到了，不计入
        }
        ckList.pop_front();
    }
}

void Dijkstra(const Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{

}

void AStar(const Map &map, const MNode &startNode, const MNode &endNode, list<MNode> &pathList)
{

}
